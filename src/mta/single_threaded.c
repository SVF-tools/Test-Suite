// single_threaded.c -- a program with NO thread-spawning calls.
//
// It never calls pthread_create, so the pre-analysis finds zero thread
// functions and the MSli pipeline takes its "no thread functions" early-out
// (nothing to slice / analyse). Keeps that guard path exercised.
#include <pthread.h>

int g_state;

static int compute(int x) { int s = x; for (int i = 0; i < 10; i++) s = s * 3 + i; return s; }

int main(void) {
    g_state = compute(7);
    for (int i = 0; i < 4; i++)
        g_state += compute(i);
    return g_state & 1;
}
