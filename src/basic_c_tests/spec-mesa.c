/*
 * Heap and structures like 177.mesa
 * Author: Sen Ye
 * Date: 09/09/2013
 */
#include "aliascheck.h"

void begin(int *p, int *q) {
	NOALIAS(p,q);
}

void end(int *p, int *q) {
	MAYALIAS(p,q); // should be NOALIAS under context-sensitive
}

void render(int *p, int *q) {
	MAYALIAS(p,q);
}

struct api_table {
	void (*Begin)(int *, int *);
	void (*End)(int *, int *);
	void (*Render)(int *, int *);
};

struct context {
	struct api_table API;
	struct api_table Exec;
};

struct mesa_context {
	struct context * ctx;
};

void init_exec_pointers(struct api_table * table) {
	table->Begin = begin;
	table->End = end;
	table->Render = render;
}

void init_api_function(struct context * ctx) {
	init_exec_pointers(&ctx->Exec);
}

struct context * create_context() {
	// Create heap objects here
	struct context * ctx = (struct context*)malloc(sizeof(struct context));
	init_api_function(ctx);
	// If field-sensitive, following statement would create another two heap
	// objects
	ctx->API = ctx->Exec;
	return ctx;
}

struct context * CC;

void change_context(struct context * ctx) {
	CC = ctx;
}

void make_current(struct mesa_context * ctx) {
	change_context(ctx->ctx);
}

void draw(int *p, int *q, int *r) {
	(*CC->API.Begin)(p, q);
	if (p)
		q = r;
	if (*CC->API.Render) {
		(*CC->API.Render)(q, r);
		(*CC->API.End)(p, r);
	}
	else
		(*CC->API.End)(q, p);
}

void delete_context(struct context * ctx) {
	free (ctx);
}

int main() {
	int x,y,z;
	struct mesa_context * mesa = (struct mesa_context*)malloc(sizeof(struct mesa_context));
	mesa->ctx = create_context();
	make_current(mesa);
	draw(&x, &y, &z);
	delete_context(mesa->ctx);
	free(mesa);
	return 0;
}
