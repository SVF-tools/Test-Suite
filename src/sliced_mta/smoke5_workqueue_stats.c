// smoke5_workqueue_stats.c -- a small request-processing workload.
//
// Worker threads run a local request pipeline and then update shared statistics
// without locks. Most request parsing, routing, checksum, and serialization code
// is local to each request; the raced statements are the final statistics
// updates.
#include <pthread.h>

typedef struct Request {
    int id;
    int user;
    int route;
    int payload[24];
    int scratch[24];
} Request;

typedef struct Response {
    int status;
    int cost;
    int bytes;
    int tags[12];
} Response;

int requests_done;
int error_count;
int route_hits[4];

static int mix32(int x) {
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

static int parse_header(Request *req, int seed) {
    req->id = mix32(seed) & 0x7fff;
    req->user = mix32(seed + 17) & 0xff;
    req->route = (req->id ^ req->user) & 3;
    return req->route;
}

static int parse_payload(Request *req, int seed) {
    int total = 0;
    for (int i = 0; i < 24; i++) {
        req->payload[i] = mix32(seed + i * 19) & 0x3ff;
        total += req->payload[i];
    }
    return total;
}

static int normalize_payload(Request *req) {
    int total = 0;
    for (int i = 0; i < 24; i++) {
        int v = req->payload[i];
        req->scratch[i] = (v < 128) ? (v + 31) : (v - 7);
        total += req->scratch[i];
    }
    return total;
}

static int apply_route_a(Request *req) {
    int score = 0;
    for (int i = 0; i < 12; i++) {
        score += req->scratch[i] * (i + 1);
    }
    return score;
}

static int apply_route_b(Request *req) {
    int score = 1;
    for (int i = 12; i < 24; i++) {
        score ^= req->scratch[i] + i * 3;
    }
    return score;
}

static int apply_route_c(Request *req) {
    int score = 0;
    for (int i = 0; i < 24; i += 2) {
        score += req->scratch[i] ^ req->scratch[i + 1];
    }
    return score;
}

static int route_request(Request *req) {
    if (req->route == 0) return apply_route_a(req);
    if (req->route == 1) return apply_route_b(req);
    if (req->route == 2) return apply_route_c(req);
    return apply_route_a(req) + apply_route_c(req);
}

static int authorize_request(Request *req, int score) {
    int token = mix32(req->user + score);
    int class_id = (token ^ req->id) & 7;
    return class_id != 6;
}

static int compute_checksum(Request *req) {
    int h = 216613626;
    for (int i = 0; i < 24; i++) {
        h = mix32(h ^ req->payload[i]);
        h = mix32(h + req->scratch[i]);
    }
    return h;
}

static int classify_request(Request *req, int checksum) {
    int c0 = (checksum ^ req->id) & 15;
    int c1 = (checksum >> 4) & 15;
    int c2 = (req->user + req->route) & 15;
    return (c0 + c1 + c2) & 15;
}

static void build_response(Response *resp, Request *req, int score, int checksum) {
    resp->status = authorize_request(req, score) ? 200 : 403;
    resp->cost = (score ^ checksum) & 0x3fff;
    resp->bytes = 64 + (resp->cost & 127);
    for (int i = 0; i < 12; i++) {
        resp->tags[i] = mix32(resp->cost + req->scratch[i]) & 0xff;
    }
}

static int serialize_response(Response *resp) {
    int bytes = resp->bytes;
    for (int i = 0; i < 12; i++) {
        bytes += (resp->tags[i] & 7);
    }
    return bytes;
}

static int endpoint_search(Request *req, Response *resp) {
    int score = req->id + resp->cost;
    score += req->payload[0] * 3;
    score ^= req->scratch[3] + req->payload[5];
    score += mix32(req->scratch[7] + score);
    score ^= req->payload[11] + req->scratch[13];
    resp->tags[0] = score & 0xff;
    resp->tags[1] = (score >> 3) & 0xff;
    return score;
}

static int endpoint_profile(Request *req, Response *resp) {
    int score = req->user * 17;
    score += req->payload[2] + req->payload[4];
    score ^= mix32(req->scratch[6] + req->scratch[8]);
    score += req->payload[10] * 5;
    score ^= req->scratch[12] + req->payload[14];
    resp->tags[2] = score & 0xff;
    resp->tags[3] = (score >> 2) & 0xff;
    return score;
}

static int endpoint_checkout(Request *req, Response *resp) {
    int score = resp->bytes;
    score += req->payload[1] * req->scratch[1];
    score ^= req->payload[3] + req->scratch[9];
    score += mix32(req->payload[15] + score);
    score ^= req->scratch[17] + req->payload[19];
    resp->tags[4] = score & 0xff;
    resp->tags[5] = (score >> 4) & 0xff;
    return score;
}

static int endpoint_inventory(Request *req, Response *resp) {
    int score = req->route + 31;
    score += req->scratch[0] + req->scratch[2];
    score ^= mix32(req->payload[6] + req->payload[8]);
    score += req->scratch[16] * 7;
    score ^= req->payload[20] + req->scratch[22];
    resp->tags[6] = score & 0xff;
    resp->tags[7] = (score >> 5) & 0xff;
    return score;
}

static int endpoint_recommend(Request *req, Response *resp) {
    int score = req->id ^ req->user;
    score += mix32(req->payload[7] + req->scratch[4]);
    score ^= req->payload[9] * 11;
    score += req->scratch[18] + req->payload[21];
    score ^= mix32(score + req->scratch[23]);
    resp->tags[8] = score & 0xff;
    resp->tags[9] = (score >> 6) & 0xff;
    return score;
}

static int endpoint_audit(Request *req, Response *resp) {
    int score = resp->status;
    score += req->payload[12] + req->payload[13];
    score ^= req->scratch[5] * 13;
    score += mix32(req->scratch[10] + req->payload[16]);
    score ^= req->scratch[21] + resp->cost;
    resp->tags[10] = score & 0xff;
    resp->tags[11] = (score >> 7) & 0xff;
    return score;
}

static int endpoint_local_report(Request *req, Response *resp) {
    int score = req->payload[0] + req->payload[23];
    score ^= req->scratch[1] + req->scratch[22];
    score += mix32(score + req->id);
    score ^= resp->bytes + req->route;
    score += req->user * 19;
    return score;
}

static int endpoint_local_cache(Request *req, Response *resp) {
    int score = req->scratch[2] + req->scratch[20];
    score += mix32(req->payload[5] + req->payload[18]);
    score ^= resp->cost + req->payload[6];
    score += req->scratch[14] * 23;
    score ^= mix32(score + resp->status);
    return score;
}

static int endpoint_billing(Request *req, Response *resp) {
    int score = req->user + resp->bytes;
    score += req->payload[4] * 29;
    score ^= req->scratch[6] + req->payload[17];
    score += mix32(resp->cost + req->scratch[19]);
    score ^= req->payload[22] + req->id;
    resp->tags[0] ^= score & 0xff;
    return score;
}

static int endpoint_shipping(Request *req, Response *resp) {
    int score = req->route * 41;
    score += req->scratch[8] + req->scratch[15];
    score ^= mix32(req->payload[1] + req->payload[21]);
    score += resp->bytes * 3;
    score ^= req->scratch[11] + req->payload[13];
    resp->tags[1] ^= (score >> 1) & 0xff;
    return score;
}

static int endpoint_fraud_check(Request *req, Response *resp) {
    int score = req->id ^ resp->status;
    score += mix32(req->user + req->payload[2]);
    score ^= req->scratch[7] * 31;
    score += req->payload[18] + req->scratch[20];
    score ^= mix32(score + resp->cost);
    resp->tags[2] ^= (score >> 2) & 0xff;
    return score;
}

static int endpoint_notification(Request *req, Response *resp) {
    int score = resp->bytes + 97;
    score += req->payload[3] + req->scratch[4];
    score ^= mix32(req->payload[12] + req->scratch[16]);
    score += req->user * 37;
    score ^= resp->status + req->route;
    resp->tags[3] ^= (score >> 3) & 0xff;
    return score;
}

static int endpoint_session(Request *req, Response *resp) {
    int score = req->id + req->user;
    score ^= req->payload[9] + req->scratch[9];
    score += mix32(req->payload[10] + req->scratch[10]);
    score ^= resp->cost * 5;
    score += req->payload[23] + resp->bytes;
    resp->tags[4] ^= (score >> 4) & 0xff;
    return score;
}

static int endpoint_localization(Request *req, Response *resp) {
    int score = req->route + req->payload[6];
    score += req->scratch[12] * 43;
    score ^= mix32(req->payload[14] + req->scratch[18]);
    score += resp->status + req->user;
    score ^= req->payload[20] + resp->cost;
    resp->tags[5] ^= (score >> 5) & 0xff;
    return score;
}

static int endpoint_ab_test(Request *req, Response *resp) {
    int score = req->id & 255;
    score += req->payload[7] + req->scratch[13];
    score ^= mix32(req->payload[15] + resp->bytes);
    score += req->scratch[21] * 47;
    score ^= req->user + resp->status;
    resp->tags[6] ^= (score >> 6) & 0xff;
    return score;
}

static int endpoint_local_metrics(Request *req, Response *resp) {
    int score = resp->cost + resp->bytes;
    score += req->payload[8] + req->scratch[0];
    score ^= mix32(req->payload[16] + req->scratch[23]);
    score += req->route * 53;
    score ^= req->id + req->payload[19];
    resp->tags[7] ^= (score >> 7) & 0xff;
    return score;
}

static int dispatch_endpoint(Request *req, Response *resp, int cls) {
    switch (cls & 15) {
    case 0: return endpoint_search(req, resp);
    case 1: return endpoint_profile(req, resp);
    case 2: return endpoint_checkout(req, resp);
    case 3: return endpoint_inventory(req, resp);
    case 4: return endpoint_recommend(req, resp);
    case 5: return endpoint_audit(req, resp);
    case 6: return endpoint_local_report(req, resp);
    case 7: return endpoint_local_cache(req, resp);
    case 8: return endpoint_billing(req, resp);
    case 9: return endpoint_shipping(req, resp);
    case 10: return endpoint_fraud_check(req, resp);
    case 11: return endpoint_notification(req, resp);
    case 12: return endpoint_session(req, resp);
    case 13: return endpoint_localization(req, resp);
    case 14: return endpoint_ab_test(req, resp);
    default: return endpoint_local_metrics(req, resp);
    }
}

static int process_request(int seed) {
    Request req;
    Response resp;
    parse_header(&req, seed);
    parse_payload(&req, seed + 100);
    normalize_payload(&req);
    int score = route_request(&req);
    int checksum = compute_checksum(&req);
    int cls = classify_request(&req, checksum);
    build_response(&resp, &req, score + cls, checksum);
    resp.cost ^= dispatch_endpoint(&req, &resp, cls);
    return serialize_response(&resp);
}

static void record_stats(int route, int bytes) {
    requests_done = requests_done + 1;
    route_hits[route & 3] = route_hits[route & 3] + 1;
    if (bytes & 1) {
        error_count = error_count + 1;
    }
}

void *worker(void *arg) {
    int seed = (int)(long)arg;
    int bytes = process_request(seed);
    record_stats(seed, bytes);
    return 0;
}

int main(void) {
    pthread_t t1, t2, t3, t4;
    pthread_create(&t1, 0, worker, (void *)11);
    pthread_create(&t2, 0, worker, (void *)23);
    pthread_create(&t3, 0, worker, (void *)37);
    pthread_create(&t4, 0, worker, (void *)41);
    record_stats(1, process_request(5));
    record_stats(2, process_request(7));
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);
    pthread_join(t4, 0);
    return requests_done + error_count;
}
