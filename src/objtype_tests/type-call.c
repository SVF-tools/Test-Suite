#include "type_check.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void foo(Node* node) {
    node->data = 1;
}

int main() {
    Node* head1 = TYPE_MALLOC(sizeof(Node), 2);
    foo(head1);
    free(head1);
    return 0;
}