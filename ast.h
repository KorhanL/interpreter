#ifndef AST_H
#define AST_H

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

node* v(int x);
node* n();
node* e(char op, node *a, node *b);
node* b(bin_op fp);
node* be(bin_op fp, node *a, node *b);

#endif
