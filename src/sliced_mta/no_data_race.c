// no_data_race.c -- a threaded program with NO data races.
//
// Two workers touch disjoint globals and main touches a third; no object is
// shared between concurrent threads, so both MSli and the whole-program FSAM
// report zero races. This exercises the pipeline's "no race pairs" paths (the
// slicing/PTA/final stages that early-out when the pre-analysis finds nothing).
#include <pthread.h>

int g_a;      // written only by worker_a
int g_b;      // written only by worker_b
int g_main;   // touched only by main

static int compute(int x) { int s = x; for (int i = 0; i < 10; i++) s = s * 3 + i; return s; }

void* worker_a(void* arg) { g_a = compute((int)(long)arg); return 0; }
void* worker_b(void* arg) { g_b = compute((int)(long)arg) ^ 7; return 0; }

int main(void) {
    pthread_t ta, tb;
    pthread_create(&ta, 0, worker_a, (void*)1);
    pthread_create(&tb, 0, worker_b, (void*)2);
    g_main = 5;                 // main-only, races nothing
    pthread_join(ta, 0);
    pthread_join(tb, 0);
    return 0;
}
