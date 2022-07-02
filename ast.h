#ifndef AST_H
#define AST_H

typedef enum {
	NIL,
	BUILTIN,
	VALUE,
	EXPRESSION,
	VARIABLE
} ntype;

typedef struct Node node;

typedef node*(*bin_op)(node*, node*);

struct Node {
	ntype type;
	// if VALUE
	int value;
	// if EXPRESSION or VARIABLE
	char op;
	node *a, *b;
	// if BUILTIN
	bin_op fp;
};

node* v(int x);
node* c(char c);
node* n();
node* e(char op, node *a, node *b);
node* b(bin_op fp);
node* be(bin_op fp, node *a, node *b);
node* copy(node *n);
node* deepcopy(node *n);
void printexpr(node *n);

#endif
