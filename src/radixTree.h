/* Define the header file */
#ifndef RADIXTREE_H
#define RADIXTREE_H


/* Inclusion of essential libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "dynamicString.h"


/* Data type definition */

// Strcut for radix tree node
typedef struct rTree rTree_t;
struct rTree {
    int prefixLength; // In bits
    char *prefix; // Contains entire common prefix
    rTree_t *branchA; // Bit after prefix is 0
    rTree_t *branchB; // Bit after prefix is 1
    list_t *dataList; // Empty list if not a leaf node
};


/* Prototype for radix tree specific functions */

// Create a new radix tree
rTree_t *newRadixTree(void);

// Insert a new node into the radix tree
rTree_t* insertNode(rTree_t *tree, char *data);

// Search for a node in the radix tree
rTree_t* searchNode(rTree_t *tree, char *key);

// Free radix tree nodes
void freeTreeNode(rTree_t *tree);

/* 
** Locate the end binary bit position of the longest common 
** prefix between two strings
*/ 
int longestCommonPrefix(char *stringA, char *stringB);

/* End of header file*/
#endif