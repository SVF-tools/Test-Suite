#include "aliascheck.h"

struct obstack {
  unsigned long chunk_size;
  void *chunk;
  char *object_base;
  char *next_free;
  char *chunk_limit;
  union
  {
    unsigned long i;
    void *p;
  } temp;
  unsigned long alignment_mask;
  union
  {
    void (*plain) (int *);
    void (*extra) (void *, unsigned long);
  } chunkfun;
  void *extra_arg;
};

struct Tokens {
  unsigned long n_tok;
  char **tok;
  unsigned long *tok_len;
  struct obstack o_data;
};

int globali;

void foo(int *i) {
    TBHC_MUSTALIAS(i, &globali);
}

void bar(int *i) {
    TBHC_NOALIAS(i, &globali);
}

void readtokens0_init(struct Tokens *t) {
    struct obstack *h = &t->o_data;
    h->chunkfun.plain = foo;
    h->chunkfun.plain(&globali);
    h->chunk_limit = (char *) h->chunk_size;
}

int main(void) {
    struct Tokens tok;
    readtokens0_init(&tok);

    int locali;
    bar(&locali);

    return 0;
}
