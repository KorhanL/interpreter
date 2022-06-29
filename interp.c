
#include <stdio.h>
#include <stdlib.h>

// since i lost the original source i now have to reconstruct it from memory :(

typedef enum {
	VALUE,
	BUILTIN,
	EXPRESSION,
	NIL
} ntype;

typedef struct ASTNode node;
typedef node*(*bin_op)(node*, node*);

struct ASTNode {
	ntype type;
	// if VALUE
	int value;
	// if EXPRESSION
	char op;
	node *a, *b;
	// if BUILTIN
	bin_op fp;
};

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
	switch(n->type) {
		// nothing to evaluate, just continue as usual
		case VALUE:
		case NIL:
			return n;
			break;
		case EXPRESSION:
			return n;
			break;
		case BUILTIN:
			return n;
			break;
	}
	return 0;
}

int main() {
	printexpr(
			e('+', e('-', v(3), v(6)), v(-4))
			);
}
