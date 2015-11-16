struct list {
    struct list * prev;
};

struct list * construct (struct list * head) {
    int i;
   if (i > 0) {
       struct list * tmp = malloc(sizeof(struct list));
       head->prev = tmp;
       return construct (tmp);

    } 
    return head;
}
int main () {
    struct list * head;
    head = malloc(sizeof(struct list));
    head->prev = 0;

    head = construct (head);
    head = head->prev;
}


