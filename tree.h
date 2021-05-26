#ifndef TREE_H
#define TREE_H

#include "node.h"

void printInorder();
void printPreorder();
void printPostorder();
struct Node * insert(struct Node * node, struct Node * insert_node);
void buildTree(char string_storage[][31], int string_length[], int rows);

#endif
