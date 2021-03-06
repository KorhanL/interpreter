#include "ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// create a NUMBER
node* n(int x) {
	node* n = malloc(sizeof(node));
	n->type = NUMBER;
	n->value.number = x;
	n->tail = 0;

	return n;
}

// create a SYMBOL
node* s(char c) {
	node* n = malloc(sizeof(node));
	n->type = SYMBOL;
	n->value.symbol = c;
	n->tail = 0;

	return n;
}

// create a NIL
node* nil() {
	node* n = malloc(sizeof(node));
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

	node* n = malloc(sizeof(node));
	n->type = EXPRESSION;
	n->value.expression = h;
	n->tail = 0;

	return n;
}

// create a PROCEDURE
node* p(fp impl, node* args) {
	node* n = malloc(sizeof(node));
	n->type = PROCEDURE;
	n->value.procedure.impl = impl;
	n->value.procedure.args = args;
	n->tail = 0;

	return n;
}

// copy a node
node* copy(node* c) {
	node* n = malloc(sizeof(node));
	n->type = c->type;
	n->value = c->value;
	n->tail = 0;

	return n;
}

// deep copy a node
// this also makes a copy of any subnodes the node has
// TODO: fix edge cases
node* deepcopy(node* c) {
	node* n = malloc(sizeof(node));
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

// get the length of a list of nodes
int nodelength(node* n) {
	int count = 0;
	while(n) {
		count++;
		n = n->tail;
	}

	return count;
}

// print an expression
void _printexpr(node* n) {
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
				_printexpr(n->value.expression);
				printf(")");
				break;
			case PROCEDURE:
				printf("[");
				printf("%p ", n->value.procedure.impl);
				_printexpr(n->value.procedure.args);
				printf("]");
				break;
			case SYMBOL:
				printf("S:%c", n->value.symbol);
				break;
		}
		if (n->tail) {
			printf(" ");
			_printexpr(n->tail);
		}
	}
}

void printexpr(node* n) {
	_printexpr(n);
	printf("\n");
}
