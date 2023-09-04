/* Define the header file */
#ifndef RADIXTREE_H
#define RADIXTREE_H


/* Inclusion of essential libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "dynamicArray.h"

/* Data type definition */

// Strcut for radix tree node
typedef struct rTreeNode rTreeNode_t;
struct rTreeNode {
    int prefixLength; // In bits
    dynamicCharArray_t *prefix; // Contains entire common prefix
    rTreeNode_t *branchA; // Bit after prefix is 0
    rTreeNode_t *branchB; // Bit after prefix is 1
    list_t *dataList; // Empty list if not a leaf node
};

/* Prototype for radix tree specific functions */

// Create a new radix tree
rTreeNode_t *newRadixTree(void);

// Insert a new node into the radix tree
rTreeNode_t* insertNode(rTreeNode_t *tree, char *key, void *data);

// Search for a node in the radix tree
rTreeNode_t* searchNode(rTreeNode_t *tree, char *key);

// Free the radix tree
void freeTree(rTreeNode_t *tree);

/* End of header file*/
#endif