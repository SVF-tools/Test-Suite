extern void * malloc(unsigned);
extern void free (void *);

struct list {
    int flag;
    struct list * next;
    struct list * prev;
};

struct list * construct (unsigned idx) {
    struct list * head;
    unsigned i = 0;
    head = malloc(sizeof(struct list));
    head->next = 0;
    head->prev = 0;
    head->flag = -1;
    for (i =0; i<idx; i++){
        struct list * cur = malloc(sizeof(struct list));
        cur->flag = idx;
        cur->next = head;
        cur->prev = 0;
        head->prev = cur;
        head = cur;
    }
    return head;
}

struct list * randomwalk (struct list * head) {
    struct list * cur = head;

    for (;cur->flag != 0; cur=cur->next) {
        if (cur->flag > 3) 
            cur = cur->prev;
    }
    return cur;
}

void main () {
    struct list * head;
    struct list * head1;
    head = construct (10);

    head1 = randomwalk (head);
}
