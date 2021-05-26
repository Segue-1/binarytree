#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
	// Pointers for tree traversal
	struct Node *head;
	struct Node *left;
	struct Node *right;

	// Value just stores the string of the node 
	// Score adds the ascii value of the first two chars
	// Score is not used yet
	// Dupe_str holds a duplicate string.
	char *value;
	char *dupe_str;
	int score, tree_level;
	bool is_dupe, has_dupe;
	
	

};

#endif
