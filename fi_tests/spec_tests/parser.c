/*
 * Aliases resulted by heap model in 197.parser.
 * Author: Sen Ye
 * Date: 09/05/2014
 */
#include "aliascheck.h"
#include <stdlib.h>

typedef struct X_node_struct X_node;
struct X_node_struct {
    int* string;
    X_node *next;
};

typedef struct Word_struct Word;
struct Word_struct {
    int* string;
    X_node * x;
};

typedef struct clause_struct Clause;
struct clause_struct {
    Clause * next;
};

/* Only one heap object O is allocated by xalloc() and
 * it will used in build_clause() and special_string().
 */
void * xalloc(int size) {
	return (void *) malloc(1000);
}

Word sentence[250];

void build_clause() {
    Clause *c=NULL, *c1, *c2;

	c1 = (Clause*) xalloc(sizeof (Clause));
	while(c1 != NULL) {
		c2 = c1->next; /* c2 = pts(c1) */
		c1->next = c;  /* pts(c1) = c */
		c = c1;        /* c = c1 */
		c1 = c2;       /* c1 = c2 */
	}
	NOALIAS(sentence[0].string, c1);
}

void special_string(int i) {
    X_node * e;
	/* The unique heap object O will points-to object of 
	   sentence's first field after following code. */
	sentence[i].x = (X_node *) xalloc(sizeof(X_node));
	for (e = sentence[i].x; e != NULL; e = e->next) {
	    e->string = sentence[i].string;
	}
}

int main() {
	build_clause();
	special_string(10);
	return 0;
}
