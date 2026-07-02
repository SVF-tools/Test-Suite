// smoke2_interproc.c -- a second smoke test exercising interprocedural slicing.
//
// A pool of worker threads reaches a shared write through a chain of helper
// calls, and main writes the same object concurrently. A separate, larger body
// of helper functions (helper_0..helper_n) does only local work and is never on
// any path to the shared state, so MSli slices it out: the slice keeps just the
// few functions that carry value flow to the racy accesses, while the race
// statements match the whole-program run. Still analyses in a second or two.
#include <pthread.h>

int shared;           // the raced object

// --- the kept core: an interprocedural path to the shared write ---
static void write_shared(int v) { shared = v; }
static void mid_layer(int v)     { write_shared(v + 1); }
static void entry_layer(int v)   { mid_layer(v * 2); }

// --- a large independent helper body that never touches `shared` (sliced away) ---
static int helper_0(int x)  { return x * 7 + 1; }
static int helper_1(int x)  { return helper_0(x) - 3; }
static int helper_2(int x)  { return helper_1(x) ^ x; }
static int helper_3(int x)  { return helper_2(x) + helper_0(x); }
static int helper_4(int x)  { return helper_3(x) * 2; }
static int helper_5(int x)  { return helper_4(x) - helper_1(x); }
static int helper_6(int x)  { return helper_5(x) + helper_2(x); }
static int helper_7(int x)  { return helper_6(x) ^ helper_3(x); }
static void local_only(int seed) {
    volatile int sink = 0;
    for (int i = 0; i < 6; i++) sink += helper_7(seed + i);
}

void* worker(void* arg) {
    local_only((int)(long)arg);  // noise -> sliced away
    entry_layer((int)(long)arg); // interprocedural path to `shared` -> race
    return 0;
}

int main(void) {
    pthread_t pool[3];
    local_only(99);              // noise -> sliced away
    for (int i = 0; i < 3; i++) pthread_create(&pool[i], 0, worker, (void*)(long)i);
    shared = 100;                // main writes `shared` concurrently -> race
    for (int i = 0; i < 3; i++) pthread_join(pool[i], 0);
    return 0;
}
