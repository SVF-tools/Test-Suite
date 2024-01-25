#include "type_check.h"


typedef struct Node {
    int data;
    struct Node *next;
} Node;
int main() {
    Node * head1 = TYPE_MALLOC(sizeof(Node), 2);

    Node* head2 = head1;
    head2->data = 1;

    free(head2);
    return 0;
}