#include "type_check.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void* malloc_wrapper() {
    return TYPE_MALLOC(sizeof(Node), 2);
}
int main() {
    Node* head1 = malloc_wrapper();
    head1->data = 1;

    free(head1);
    return 0;
}