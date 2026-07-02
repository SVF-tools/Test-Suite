// smoke1_basic.c -- a minimal smoke test for the MSli artifact.
//
// Two worker threads share a counter and a flag; main also touches them. Most of
// the program is independent local arithmetic (compute_*) that never touches the
// shared state, so MSli slices it away -- the analysed slice is far smaller than
// the whole program, yet the reported race statements are identical to the
// whole-program (FSAM) run. Analyses quickly.
#include <pthread.h>

int counter;          // shared, written by several threads  -> race
int flag;             // shared, written/read concurrently    -> race
int done_local;       // thread-local-ish bookkeeping

// --- independent computation that touches no shared state (sliced away) ---
static int compute_a(int x) { int s = x; for (int i = 0; i < 10; i++) s = s * 3 + i; return s; }
static int compute_b(int x) { return compute_a(x) ^ (x << 2); }
static int compute_c(int x) { int s = 0; for (int i = 0; i < 8; i++) s += compute_b(x + i); return s; }

static void busy_work(int seed) {
    volatile int sink = 0;
    for (int i = 0; i < 4; i++) sink += compute_c(seed + i);
}

void* worker(void* arg) {
    busy_work((int)(long)arg);   // noise -> sliced away
    counter = counter + 1;       // shared write  -> races with the other workers
    flag = 1;                    // shared write  -> races with main's read
    return 0;
}

int main(void) {
    pthread_t t1, t2;
    busy_work(42);               // noise -> sliced away
    pthread_create(&t1, 0, worker, (void*)1);
    pthread_create(&t2, 0, worker, (void*)2);
    int r = flag;                // concurrent read of flag -> race
    counter = r;                 // concurrent write of counter -> race
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    return 0;
}
