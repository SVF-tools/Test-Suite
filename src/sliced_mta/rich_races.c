// rich_races.c -- a denser test for preservation checks.
//
// This case has several independently reachable race statements: direct shared
// writes, pointer-indirect writes, interprocedural writes, and array element
// updates. The surrounding local-only computation is irrelevant to the races and
// should be sliced away. If slicing loses one of the racy paths, the RQ2 table's
// Preserved column should expose the mismatch.
#include <pthread.h>

int shared_a;
int shared_b;
int shared_c;
int shared_array[4];

static int local_mix(int x) {
    int v = x;
    for (int i = 0; i < 12; i++) {
        v = (v * 17 + i) ^ (v >> 1);
    }
    return v;
}

static void local_only(int seed) {
    volatile int sink = 0;
    for (int i = 0; i < 8; i++) {
        sink += local_mix(seed + i);
    }
}

static void write_indirect(int *p, int v) {
    *p = v;
}

static void write_chain3(int v) {
    shared_c = v;
}

static void write_chain2(int v) {
    write_chain3(v + 11);
}

static void write_chain1(int v) {
    write_chain2(v * 3);
}

static void touch_array(int idx, int v) {
    shared_array[idx & 3] = v;
}

void *worker_direct(void *arg) {
    long id = (long)arg;
    local_only((int)id);
    shared_a = (int)id;
    shared_b = shared_a + 1;
    return 0;
}

void *worker_indirect(void *arg) {
    long id = (long)arg;
    local_only((int)id + 20);
    write_indirect(&shared_b, (int)id);
    write_chain1((int)id);
    return 0;
}

void *worker_array(void *arg) {
    long id = (long)arg;
    local_only((int)id + 40);
    touch_array((int)id, (int)id * 5);
    touch_array(1, (int)id * 7);
    return 0;
}

int main(void) {
    pthread_t t1, t2, t3, t4;
    local_only(100);
    pthread_create(&t1, 0, worker_direct, (void *)1);
    pthread_create(&t2, 0, worker_indirect, (void *)2);
    pthread_create(&t3, 0, worker_array, (void *)3);
    pthread_create(&t4, 0, worker_array, (void *)5);
    shared_a = 9;
    write_indirect(&shared_b, 10);
    write_chain1(11);
    shared_array[1] = shared_c;
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);
    pthread_join(t4, 0);
    return 0;
}
