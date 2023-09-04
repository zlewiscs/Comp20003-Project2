#include "radixTree.h"

// Create a new radix tree
rTreeNode_t *newRadixTree(void) {
    rTreeNode_t *tree = malloc(sizeof(rTreeNode_t));
    assert(tree);
    tree->prefixLength = 0;
    tree->prefix = createDynamicCharArray();
    tree->branchA = NULL;
    tree->branchB = NULL;
    tree->dataList = NULL;
    return tree;
}

// Insert a new node into the radix tree

// Search for a node in the radix tree

// Free the radix tree recursively
void freeTree(rTreeNode_t *tree) {
    if (tree->branchA != NULL) {
        freeTree(tree->branchA);
    }
    if (tree->branchB != NULL) {
        freeTree(tree->branchB);
    }
    if (tree->dataList != NULL) {
        freeList(tree->dataList);
    }
    freeDynamicCharArray(tree->prefix);
    free(tree);
}