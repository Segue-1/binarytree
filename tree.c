#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>

#include "node.h"


// Print functions
void printInorder(struct Node *node){
	
	if(node != NULL) {
		printInorder(node->left);
		int r = 0;
		for (r = 0; r < node->tree_level; r++) {
			printf("    ");
		}
		printf(" %s ", node->value);
		if (node->has_dupe == true) {
			printf("- %s ", node->dupe_str);
		}
		printf("\n");
		printInorder(node->right);
	}	
}


void printPreorder(struct Node *node) {

	if(node != NULL) {
		int r;
		for (r = 0; r < node->tree_level; r++) {
			printf("    ");
		}		
		printf(" %s ", node->value);
		if (node->has_dupe == true) {
			printf("- %s ", node->dupe_str);
		}
		printf("\n");		
		printPreorder(node->left);
		printPreorder(node->right);

	}
}


void printPostorder(struct Node *node) {

	if(node != NULL) {
		printPostorder(node->left);
		printPostorder(node->right);
		int r;
		for (r = 0; r < node->tree_level; r++) {
			printf("    ");
		}		
		printf(" %s ", node->value);
		if (node->has_dupe == true) {
			printf("- %s ", node->dupe_str);
		}
		printf("\n");
	}
}


// Inserts nodes into the tree
struct Node * insert(struct Node * node, struct Node * insert_node) {

	if (node == NULL) {
		return insert_node;
	}

	if (insert_node->score < node->score) {
		insert_node->tree_level++;
		node->left = insert(node->left, insert_node);
	}
	else if (insert_node->score > node->score) {
		insert_node->tree_level++;
		node->right = insert(node->right, insert_node);
	}


	return node;
}


void buildTree(char string_storage[][31], int string_length[], int rows){
	
	// Create array of nodes and an array of node pointers
	struct Node node_array[rows];
	struct Node *node_arrayPtr[rows];
	

	int j;
	int k;

	 
	// Link array of nodes and array of node pointers together
	// Initialize members / allocate space for strings
	int i;
	for (i = 0; i < rows; i++) {
		node_arrayPtr[i] = &node_array[i];
		node_array[i].value = malloc(31 * sizeof (char));
		node_array[i].dupe_str = malloc(31 * sizeof (char));
		node_array[i].has_dupe = false;
		node_array[i].is_dupe = false;
		node_array[i].tree_level = 0;
	
	}


	// Set value of each node
	for (k = 0; k < rows; k++) {
			for (j = 0; j < string_length[k]; j++) {
				node_array[k].value[j] = string_storage[k][j];
			}

	node_array[k].value[j] = '\0';
	}
	

	// Set score of each node based on ascii value of first two chars
	int temp_score = 0;
	for (k = 0; k < rows; k++) {
		for (j = 0; j < 2; j++) {
			temp_score += (int)(node_array[k].value[j]);
		}

	node_array[k].score = temp_score;
	temp_score = 0;
	}


	// Find duplicates based on first 2 chars using linear search
	// Also mark everything that has a duplicate or is a duplicate
	for (k = 0; k < (rows - 1) ; k++) {
		for (i = k + 1; i < rows; i++) {
			if (node_array[k].value[0] == node_array[i].value[0] && 
			    node_array[k].value[1] == node_array[i].value[1]) {
 				if (node_array[k].has_dupe == false &&
				    node_array[i].is_dupe == false) {
					node_array[k].has_dupe = true;
					node_array[i].is_dupe = true;
					strcpy(node_array[k].dupe_str, node_array[i].value);
				}
				else {
					node_array[i].is_dupe = true;
				}
			}
		}
		
	}



	// Set all nodes pointers to NULL	
	for (i = 0; i < rows; i++) {
		node_array[i].head = NULL;
		node_array[i].left = NULL;
		node_array[i].right = NULL;
	}


	// Insert nodes into tree strcuture
	for (i = 0; i < rows; i++) {
		insert(node_arrayPtr[0], node_arrayPtr[i]);
	}

	
	// Print traversals to screen
	printf("---------In order traversal-----------\n");
	printInorder(node_arrayPtr[0]);
	printf("--------------------------------------\n");


	printf("---------Pre order traversal----------\n");
	printPreorder(node_arrayPtr[0]);
	printf("--------------------------------------\n");


	printf("---------Post order traversal---------\n");
	printPostorder(node_arrayPtr[0]);
	printf("--------------------------------------\n");


	// Call functions again but redirect STDOUT to log files
	freopen("output.inorder", "w", stdout);
	printf("---------In order traversal-----------\n");
	printInorder(node_arrayPtr[0]);
	printf("--------------------------------------\n");


	freopen("output.preorder", "w", stdout);
	printf("---------Pre order traversal----------\n");
	printPreorder(node_arrayPtr[0]);
	printf("--------------------------------------\n");


	freopen("output.postorder", "w", stdout);
	printf("---------Post order traversal---------\n");
	printPostorder(node_arrayPtr[0]);
	printf("--------------------------------------\n");


}
