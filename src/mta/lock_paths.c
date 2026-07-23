#include <pthread.h>

typedef struct Item {
    int count;
    int shadow;
} Item;

pthread_mutex_t primary_lock;
pthread_mutex_t secondary_lock;
Item global_item;
int unlocked_total;

static void lock_primary(void) {
    pthread_mutex_lock(&primary_lock);
}

static void unlock_primary(void) {
    pthread_mutex_unlock(&primary_lock);
}

static void locked_increment(Item *item, int delta) {
    lock_primary();
    item->count += delta;
    item->shadow = item->count + delta;
    unlock_primary();
}

static void nested_locked_update(Item *item, int delta) {
    pthread_mutex_lock(&primary_lock);
    item->count += delta;
    pthread_mutex_lock(&secondary_lock);
    item->shadow += item->count;
    pthread_mutex_unlock(&secondary_lock);
    pthread_mutex_unlock(&primary_lock);
}

static void conditional_update(Item *item, int delta) {
    if (delta & 1) {
        pthread_mutex_lock(&primary_lock);
        item->count += delta;
        pthread_mutex_unlock(&primary_lock);
    } else {
        item->count += delta;
    }
}

static void *locked_worker(void *arg) {
    long id = (long)arg;
    locked_increment(&global_item, (int)id);
    nested_locked_update(&global_item, (int)id + 3);
    conditional_update(&global_item, (int)id + 4);
    unlocked_total += global_item.count;
    return 0;
}

int main(void) {
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, 0, locked_worker, (void *)1);
    pthread_create(&t2, 0, locked_worker, (void *)2);
    conditional_update(&global_item, 8);
    unlocked_total += global_item.shadow;
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    return unlocked_total;
}
