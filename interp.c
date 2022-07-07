#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "env.h"


void die(char *reason) {
	printf("Oh no! %s :(\n", reason);
	exit(1);
}

node *eval(node* n, envnode *env);

node *add(node* rand, envnode* env) {
	if (nodelength(rand) < 2)
		die("add was called with less than two operands");
	int sum = 0;
	do {
		rand = eval(rand, env);
		if(rand->type != NUMBER)
			die("add was called with wrong types");
		sum += rand->value.number;
	} while ((rand = rand->tail));

	return n(sum);
}

/*
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

node *eval(node* n, envnode *env) {
	if (!n)
		die("eval was called with null pointer");
	node *r = 0;
	switch(n->type) {
		// These evaluate to themselves
		case NIL:
		case NUMBER:
			r = n;
			break;

		// Turn the head of the list into a procedure,
		// then apply it to the tail
		case EXPRESSION:
			if (!n->value.expression)
				die("Cannot evaluate empty list");
			r = eval(n->value.expression, env);
			if (r->type != PROCEDURE)
				die("First member of expression wasn't a procedure");
			if (r->value.procedure.args)
				die("Procedure in expression had arguments (VERY BAD)");
			r->value.procedure.args = r->tail;
			r->tail = 0;
			r = eval(r, env);
			free(n);
			break;

		// Apply the procedure to its arguments
		// The procedure is responsible for deciding if
		// it evaluates its operands
		case PROCEDURE:
			r = n->value.procedure.impl(
					n->value.procedure.args, env);
			break;

		// Replace the symbol with the definition from
		// the environment
		case SYMBOL:
			if(!(r = envget(&env, n->value.symbol)))
				die("Unbound symbol");
			r->tail = n->tail;
			free(n);
			break;
	}
	/* not sure if this should be here
	if (r->tail)
		r->tail = eval(r->tail, env);
	*/
	return r;
}

int main() {
	envnode *env = 0;

	envput(&env, '+', p(&add, 0));
	envput(&env, 'x', n(3));
	/*
	envput(&env, '-', b(&sub));
	envput(&env, '*', b(&mul));
	envput(&env, 'c', b(&cons));
	envput(&env, 'l', b(&let));
	*/

	/*
	node *expr = e(
			s('*'),
			n(10),
			e(
				s('-'),
				e(
					s('+'),
					n(3),
					n(6)),
				n(-4)));
	//node *expr = e('c', v(3), e('c', v(2), n()));
	*/

	node *expr = e(s('+'), s('x'), n(1), n(3), n(6), n(-1));
	
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
	printexpr(eval(expr , env));
	printf("\n");
}
