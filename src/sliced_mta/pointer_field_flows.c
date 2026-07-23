#include <pthread.h>

typedef struct Node {
    int value;
    int aux;
    struct Node *next;
} Node;

pthread_mutex_t node_lock;
Node nodes[3];
Node *shared_head;
int global_sink;

static Node *select_node(int idx) {
    return &nodes[idx % 3];
}

static void init_nodes(void) {
    nodes[0].next = &nodes[1];
    nodes[1].next = &nodes[2];
    nodes[2].next = &nodes[0];
    shared_head = &nodes[0];
}

static void write_chain(Node *node, int value) {
    node->value = value;
    node->next->aux = value + node->value;
}

static void locked_chain(Node *node, int value) {
    pthread_mutex_lock(&node_lock);
    node->value += value;
    node->next->aux += node->value;
    pthread_mutex_unlock(&node_lock);
}

static int read_chain(Node *node) {
    return node->value + node->next->aux;
}

static void *field_worker(void *arg) {
    long id = (long)arg;
    Node *node = select_node((int)id);
    write_chain(node, (int)id + 5);
    locked_chain(shared_head->next, (int)id);
    global_sink += read_chain(node->next);
    return 0;
}

int main(void) {
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    init_nodes();
    pthread_create(&t1, 0, field_worker, (void *)1);
    pthread_create(&t2, 0, field_worker, (void *)2);
    pthread_create(&t3, 0, field_worker, (void *)3);
    write_chain(shared_head, 11);
    global_sink += read_chain(shared_head);
    pthread_join(t1, 0);
    pthread_join(t2, 0);
    pthread_join(t3, 0);
    return global_sink;
}
