#ifndef ast_h
#define ast_h

#include <stddef.h>
#include "vararg.h"
#include "typedefs.h"
#include "env.h"

typedef enum {
	NIL,
	SYMBOL,
	EXPRESSION,
	PROCEDURE,
	NUMBER
} ntype;

typedef struct Procedure {
	fp impl;
	node* args;
} proc;

typedef union NValue {
	char symbol;
	node* expression;
	proc procedure;
	int number;
} nvalue;

struct Node {
	node* tail;
	ntype type;
	nvalue value;
};

// leaves
node* n(int x);
node* s(char c);
node* nil();

// list
node* _e(size_t count, ...);
#define e(...) _e(PP_NARG(__VA_ARGS__), __VA_ARGS__)

// for internal use
node* p(fp impl, node* args);
node* copy(node* n);
node* deepcopy(node* n);

int nodelength(node* n);
void printexpr(node* n);

#endif
