#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// create a NUMBER
node* n(int x) {
	node *n = malloc(sizeof(node));
	n->type = NUMBER;
	n->value.number = x;
	n->tail = 0;

	return n;
}

// create a SYMBOL
node* s(char c) {
	node *n = malloc(sizeof(node));
	n->type = SYMBOL;
	n->value.symbol = c;
	n->tail = 0;

	return n;
}
// create a NIL
node* nil() {
	node *n = malloc(sizeof(node));
	n->type = NIL;
	n->tail = 0;

	return n;
}

// create an EXPRESSION
node* _e(size_t count, ...) {
	va_list args;
	va_start(args, count);
	node* h = va_arg(args, node*);
	node* p = h;
	while(--count) {
		p->tail = va_arg(args, node*);
		p = p->tail;
	}

	node *n = malloc(sizeof(node));
	n->type = EXPRESSION;
	n->value.expression = h;
	n->tail = 0;

	return n;
}


// create a PROCEDURE
node* p(proc fp) {
	node *n = malloc(sizeof(node));
	n->type = PROCEDURE;
	n->value.procedure = fp;
	n->tail = 0;

	return n;
}

// copy a node
node* copy(node *c) {
	node *n = malloc(sizeof(node));
	n->type = c->type;
	n->value = c->value;
	n->tail = 0;

	return n;
}

// deepcopy a node
// this also makes a copy of any subnodes the node has
node* deepcopy(node *c) {
	node *n = malloc(sizeof(node));
	n->type = c->type;

	if (c->tail)
		n->tail = deepcopy(c->tail);
	else
		n->tail = 0;

	if (c->type == EXPRESSION)
		n->value.expression = deepcopy(c->value.expression);
	else
		n->value = c->value;

	return n;
}

// print an expression
void printexpr(node *n) {
	if (!n)
		printf("null pointer node");
	else {
		switch(n->type) {
			case NUMBER:
				printf("%d", n->value.number);
				break;
			case NIL:
				printf("NIL");
				break;
			case EXPRESSION:
				printf("(");
				printexpr(n->value.expression);
				printf(")");
				break;
			case PROCEDURE:
				printf("(%p ", n->value.procedure);
				break;
			case SYMBOL:
				printf("S:%c", n->value.symbol);
				break;
		}
		if (n->tail) {
			printf(" ");
			printexpr(n->tail);
		}
	}
}
