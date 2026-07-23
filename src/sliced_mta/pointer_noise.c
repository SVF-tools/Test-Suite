// pointer_noise.c -- pthread races with unrelated pointer-heavy code.
#include <pthread.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int hot_a;
int hot_b;
Node pool[32];

#define TOUCH_NODE(i, seed)                 \
    do {                                    \
        pool[(i)].value = (seed) + (i);     \
        pool[(i)].next = &pool[((i) + 1) & 31]; \
    } while (0)

#define TOUCH_8(base, seed)     \
    TOUCH_NODE((base) + 0, seed); \
    TOUCH_NODE((base) + 1, seed); \
    TOUCH_NODE((base) + 2, seed); \
    TOUCH_NODE((base) + 3, seed); \
    TOUCH_NODE((base) + 4, seed); \
    TOUCH_NODE((base) + 5, seed); \
    TOUCH_NODE((base) + 6, seed); \
    TOUCH_NODE((base) + 7, seed)

static int pointer_noise(int seed) {
    TOUCH_8(0, seed);
    TOUCH_8(8, seed);
    TOUCH_8(16, seed);
    TOUCH_8(24, seed);
    Node *p = &pool[seed & 31];
    int sum = 0;
    for (int i = 0; i < 16; i++) {
        sum += p->value;
        p = p->next;
    }
    return sum;
}

static void write_hot(int v) {
    hot_a = v;
    hot_b = hot_a + 1;
}

void *worker_a(void *arg) {
    int v = (int)(long)arg;
    pointer_noise(v);
    write_hot(v);
    return 0;
}

void *worker_b(void *arg) {
    int v = (int)(long)arg;
    pointer_noise(v + 10);
    hot_b = v * 3;
    hot_a = hot_b + 1;
    return 0;
}

int main(void) {
    pthread_t t1, t2, t3;
    pointer_noise(100);
    pthread_create(&t1, 0, worker_a, (void *)1);
    pthread_create(&t2, 0, worker_b, (void *)2);
    pthread_create(&t3, 0, worker_a, (void *)3);
    hot_a = 7;
    hot_b = hot_a;
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);
    return 0;
}
