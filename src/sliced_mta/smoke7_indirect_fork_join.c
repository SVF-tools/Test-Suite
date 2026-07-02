#include <pthread.h>

typedef void *(*entry_fn)(void *);

pthread_t workers[4];
int shared_slots[4];
int shared_sum;

static void update_slot(int idx, int value) {
    shared_slots[idx & 3] = value;
    shared_sum += shared_slots[idx & 3];
}

static void *worker_a(void *arg) {
    long id = (long)arg;
    update_slot((int)id, (int)id + 10);
    shared_sum += (int)id;
    return 0;
}

static void *worker_b(void *arg) {
    long id = (long)arg;
    update_slot((int)id + 1, (int)id + 20);
    shared_slots[1] += shared_sum;
    return 0;
}

static entry_fn pick_worker(int flag) {
    if (flag)
        return worker_a;
    return worker_b;
}

static void spawn_pair(int base) {
    entry_fn first = pick_worker(base & 1);
    entry_fn second = pick_worker((base + 1) & 1);
    pthread_create(&workers[base], 0, first, (void *)(long)(base + 1));
    pthread_create(&workers[base + 1], 0, second, (void *)(long)(base + 2));
}

int main(void) {
    spawn_pair(0);
    spawn_pair(2);
    shared_slots[2] = shared_sum;
    pthread_join(workers[0], 0);
    pthread_join(workers[1], 0);
    pthread_join(workers[2], 0);
    pthread_join(workers[3], 0);
    return shared_slots[0] + shared_sum;
}
