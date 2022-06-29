#include "ast.h"
#include <stdlib.h>

// create a value
node* v(int x) {
	node *n = malloc(sizeof(node));
	n->type = VALUE;
	n->value = x;
	n->op = 0;
	n->a = 0;
	n->b = 0;
	n->fp = 0;

	return n;
}

// create a nil
node* n() {
	node *n = malloc(sizeof(node));
	n->type = NIL;
	n->value = 0;
	n->op = 0;
	n->a = 0;
	n->b = 0;
	n->fp = 0;

	return n;
}

// create an expression
node* e(char op, node *a, node *b) {
	node *n = malloc(sizeof(node));
	n->type = EXPRESSION;
	n->value = 0;
	n->op = op;
	n->a = a;
	n->b = b;
	n->fp = 0;

	return n;
}

// create a builtin
node* b(bin_op fp) {
	node *n = malloc(sizeof(node));
	n->type = BUILTIN;
	n->value = 0;
	n->op = 0;
	n->a = 0;
	n->b = 0;
	n->fp = fp;

	return n;
}

node* be(bin_op fp, node *a, node *b) {
	node *n = malloc(sizeof(node));
	n->type = BUILTIN;
	n->value = 0;
	n->op = 0;
	n->a = a;
	n->b = b;
	n->fp = fp;

	return n;
}

// copy a node
node* copy(node *c) {
	node *n = malloc(sizeof(node));
	n->type = c->type;
	n->value = c->value;
	n->op = c->op;
	n->a = c->a;
	n->b = c->b;
	n->fp = c->fp;

	return n;
}
