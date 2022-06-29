
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

void die(char *reason) {
	printf("Oh no! %s\n", reason);
	exit(1);
}


node *add(node *a, node *b) {
	if (a->type != VALUE || b->type != VALUE)
		die("add called with wrong types");
	return v(a->value + b->value);
}

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
		}
}

node *eval(node* n) {
	node *r = 0;
	switch(n->type) {
		// nothing to evaluate, just continue as usual
		case VALUE:
		case NIL:
			r = n;
			break;
		// substitute with something from the environment, eval subtrees then eval new expression
		case EXPRESSION:
			die("expression evaluaton not implemented");
			break;
		// just run the code
		case BUILTIN:
			r = n->fp(eval(n->a), eval(n->b));
			break;
	}
	return r;
}

int main() {
	printexpr(eval(
			be(&add, be(&add, v(3), v(6)), v(-4))
			));
}
