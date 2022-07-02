#include "ll.h"
#include <stdlib.h>

node* envget(envnode **env, char toget) {
	for (envnode *n = *env; n; n = n->next) {
		if (n->key == toget)
			return deepcopy(n->value);
	}
	return 0;
}

void envput(envnode **env, char key, node* value) {
	envnode *new = malloc(sizeof(envnode));
	new->value = deepcopy(value);
	new->key = key;
	new->next = *env;
	*env = new;
}
