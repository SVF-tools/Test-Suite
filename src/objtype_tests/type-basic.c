#include "type_check.h"

typedef struct Node {
    int data;
    struct Node *next;
} Node;
int main() {
    Node* head1 = TYPE_MALLOC(sizeof(Node), 2);
    head1->data = 1;

    free(head1);
    return 0;
}