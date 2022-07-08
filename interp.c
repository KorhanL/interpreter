#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "env.h"


void die(char* reason) {
	printf("Oh no! %s :(\n", reason);
	exit(1);
}

node* eval(node* n, envnode* env);


node* add(node* rand, envnode* env) {
	int sum = 0;
	while (rand) {
		rand = eval(rand, env);
		if(rand->type != NUMBER)
			die("add was called with wrong types");
		sum += rand->value.number;
		rand = rand->tail;
	}
	
	return n(sum);
}

node* mul(node* rand, envnode* env) {
	int prod = 1;
	while (rand) {
		rand = eval(rand, env);
		if(rand->type != NUMBER)
			die("add was called with wrong types");
		prod *= rand->value.number;
		rand = rand->tail;
	}
	
	return n(prod);
}

node *sub(node* rand, envnode* env) {
	int a = 0, b = 0;
	int length = nodelength(rand);
	if (length == 1) {
		rand = eval(rand, env);
		if(rand->type != NUMBER)
			die("sub was called with wrong types");
		b = rand->value.number;
	}
	else if (length == 2) {
		rand = eval(rand, env);
		node *tail = eval(rand->tail, env);
		if(rand->type != NUMBER || tail->type != NUMBER)
			die("sub was called with wrong types");
		a = rand->value.number;
		b = tail->value.number;
	}
	else
		die("sub called with wrong arity");

	return n(a - b);
}

node *print(node* rand, envnode* env) {
	printexpr(rand);
	return eval(rand, env);
}


node *eval(node* n, envnode* env) {
	if (!n)
		die("eval was called with null pointer");
	node *r = 0;
	switch(n->type) {
		// These evaluate to themselves
		case NIL:
		case NUMBER:
			return n;
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
			r = eval(r, env);
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
			break;
	}
	r->tail = n->tail;
	free(n);
	return r;
}

int main() {
	envnode *env = 0;

	envput(&env, '+', p(&add, 0));
	envput(&env, '-', p(&sub, 0));
	envput(&env, '*', p(&mul, 0));

	envput(&env, 'p', p(&print, 0));
	envput(&env, '3', n(3));

	node *expr;

	expr = e(s('+'),
			s('3'),
			e(s('+'), n(4), n (4)),
			n(1),
			n(3),
			n(6),
			e(s('-'), n(1)),
			n(1),
			n(0),
			n(0),
			e(s('-'), n(100), n (100)),
			n(0),
			n(0)
		);
	printexpr(expr);
	printexpr(eval(expr , env));

	expr = e(s('+'));
	printexpr(expr);
	printexpr(eval(expr , env));

	expr = e(s('*'), n(10), e(s('+'), n(5), n(4)), n(-1));
	printexpr(expr);
	printexpr(eval(expr , env));
}
