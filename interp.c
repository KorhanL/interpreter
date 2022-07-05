#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "env.h"

// Fixes TODO:
// Change the AST node so that it is more like a linked list
// there's a next pointer, and a union for the contained value
// when evaluating, assume the first member of the list is a procedure
// and look it up in the environment
//
// the execution of builtin functions and the further evaluation should
// be more closely coupled so that the builtins can have some degree of
// influence over the evaluation order
// (let) needs to be able to 'pause' the evaluation to complete the substitution

void die(char *reason) {
	printf("Oh no! %s\n", reason);
	exit(1);
}

/*
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
*/


/*
node *eval(node* n, envnode *env) {
	node *r = 0;
	switch(n->type) {
		// nothing to evaluate, just continue as usual
		case NIL:
		case SYMBOL:
		case NUMBER:
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
		case PROCEDURE:
			r = n->fp(eval(n->a, env), eval(n->b, env));
			break;
	}
	return r;
}
*/

int main() {
	//envnode *env = 0;
	/*
	envput(&env, '+', b(&add));
	envput(&env, '-', b(&sub));
	envput(&env, '*', b(&mul));
	envput(&env, 'c', b(&cons));
	envput(&env, 'l', b(&let));
	*/

	node *expr = e(3,
			s('*'),
			n(10),
			e(3,
				s('-'),
				e(3,
					s('+'),
					n(3),
					n(6)),
				n(-4)));
	//node *expr = e('c', v(3), e('c', v(2), n()));
	
	/*
	node *expr = e('l',
				// Binidngs
				e('c', e('c', c('x'), v(6)),
				e('c', e('c', c('y'), v(5)),
				n())),
				// body
				e('+', c('x'), c('y')));
	*/
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
	//printexpr(eval(expr , env));
	printf("\n");
}
