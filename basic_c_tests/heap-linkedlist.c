/*
 * Heap
 * Author: Sen Ye
 * Date: 15/10/2013
 * Description: heap objects are identified according to their
 *		allocation sites.
 */
#include "aliascheck.h"

struct Node {
	int *data;
	struct Node *next;
};

// return two malloc object
void malloc_list(struct Node *p, int num) {
	int *p_data1=NULL, *p_data2=NULL;
	struct Node *p_next = NULL;
    p->data = NULL;
	while (num!=0) {
		p->data = (int *) malloc(sizeof(int));
		p_data1 = p->data;
	    p_next = (struct Node*) malloc(sizeof(struct Node));
		p->next = p_next;
		p_data2 = p->data;
        num--;
	}
	MAYALIAS(p_data1, p_data2);
	NOALIAS(p_next, p_data1);
}

int main() {
	struct Node* head = (struct Node*) malloc(sizeof(struct Node));
	int num = 4;
	malloc_list(head, num);
	NOALIAS(head->next->data, head->next->next);
	return 0;
}
