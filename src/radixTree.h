/* Define the header file */
#ifndef RADIXTREE_H
#define RADIXTREE_H


/* Inclusion of essential libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

/* Data type definition */
// Strcut for radix tree node
typedef struct radixTreeNode radixTreeNode_t;
struct radixTreeNode {
    int commonPrefixBits;
    char *prefix;
    radixTree_t *branchA;
    radixTree_t *branchB;
    list_t *dataList;

};

// Struct for radix tree
typedef struct radixTree {
    radixTreeNode_t *root;
} radixTree_t;


/* End of header file*/
#endif