#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "ll.h"

void die(char *reason) {
	printf("Oh no! %s\n", reason);
	exit(1);
}

node *add(node *a, node *b) {
	if (a->type != VALUE || b->type != VALUE)
		die("add called with wrong types");
	return v(a->value + b->value);
}

node *sub(node *a, node *b) {
	if (a->type != VALUE || b->type != VALUE)
		die("sub called with wrong types");
	return v(a->value - b->value);
}

node *mul(node *a, node *b) {
	if (a->type != VALUE || b->type != VALUE)
		die("mul called with wrong types");
	return v(a->value * b->value);
}

// this probably isn't right, this is less
// like cons and more like a pair
node *cons(node *a, node *b) {
	return e('c', a, b);
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
			case VARIABLE:
				printf("v:%c", n->op);
				break;
				break;
		}
}

// spaghetti
node *let(node *bindings, node *body) {
	printf("bindings:");
	printexpr(bindings);
	printf("\nbody:");
	printexpr(body);
	printf("\n");
	if (body->type ==  VARIABLE)
		for (; bindings->type != NIL; bindings = bindings->b) {
			if (bindings->type != EXPRESSION && bindings->op != 'c')
				die("Invalid binding list for let");
			if (bindings->a->type != EXPRESSION && bindings->a->op != 'c')
				die("Invalid binding list for let");

			node *var = bindings->a->a;
			node *sub = bindings->a->b;

			if (var->type != VARIABLE)
				die("Invalid binding list for let");
			if (body->op == var->op)
				return deepcopy(sub);
		}
	else if (body->type == EXPRESSION)
		return e(body->op, let(bindings, body->a), let(bindings, body->b));
	return body;
}


node *eval(node* n, envnode *env) {
	node *r = 0;
	switch(n->type) {
		// nothing to evaluate, just continue as usual
		case VALUE:
		case NIL:
		case VARIABLE:
			r = n;
			break;
		// substitute with something from the environment
		// eval subtrees then eval new expression
		case EXPRESSION:
			if (!(r = envget(&env, n->op)))
				die("Undefined operator");
			r->a = n->a;
			r->b = n->b;
			r = eval(r, env);
			break;
		// just run the code
		case BUILTIN:
			r = n->fp(eval(n->a, env), eval(n->b, env));
			break;
	}
	return r;
}

int main() {
	envnode *env = 0;
	envput(&env, '+', b(&add));
	envput(&env, '-', b(&sub));
	envput(&env, '*', b(&mul));
	envput(&env, 'c', b(&cons));
	envput(&env, 'l', b(&let));

	//node *expr = e('*', v(10), e('-', e('+', v(3), v(6)), v(-4)));
	//node *expr = e('c', v(3), e('c', v(2), n()));
	node *expr = e('l',
				// Binidngs
				e('c', e('c', c('x'), v(6)),
				e('c', e('c', c('y'), v(5)),
				n())),
				// body
				e('+', c('x'), c('y')));
	/*
	node *expr = e('l',
				// Binidngs
				e('c', e('c', c('y'), v(6)),
				n()),
				// body
				c('y'));
				*/

	printexpr(expr);
	printf("\n");
	printexpr(eval(expr , env));
	printf("\n");
}
