#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

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

// create a variable
node* c(char c) {
	node *n = malloc(sizeof(node));
	n->type = VARIABLE;
	n->value = 0;
	n->op = c;
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

// deepcopy a node
// this also makes a copy of any subnodes the node has
node* deepcopy(node *c) {
	node *n = malloc(sizeof(node));
	n->type = c->type;
	n->value = c->value;
	n->op = c->op;

	if (c->a)
		n->a = deepcopy(c->a);
	else
		n->a = 0;
	if (c->b)
		n->b = deepcopy(c->b);
	else
		n->b = 0;
	n->fp = c->fp;
	return n;
}

// print an expression
void printexpr(node *n) {
	if (!n)
		printf("null pointer node");
	else
		switch(n->type) {
			// nothing to evaluate, just continue as usual
			case VALUE:
				printf("%d", n->value);
				break;
			case NIL:
				printf("NIL");
				break;
			case EXPRESSION:
				printf("(%c ", n->op);
				printexpr(n->a);
				printf(" ");
				printexpr(n->b);
				printf(")");
				break;
			case BUILTIN:
				printf("(%p ", n->fp);
				printexpr(n->a);
				printf(" ");
				printexpr(n->b);
				printf(")");
				break;
			case VARIABLE:
				printf("v:%c", n->op);
				break;
				break;
		}
}
