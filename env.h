#ifndef env_h
#define env_h

#include "ast.h"

typedef struct EnvNode envnode;

struct EnvNode {
	envnode *next;
	char key;
	node *value;
};

node* envget(envnode **env, char toget);
void envput(envnode **env, char key, node* value);

#endif
