#include "radixTree.h"
#include "bitWiseOp.h"
#include "bitWiseOp.h"

// Create a new radix tree
rTree_t *newRadixTree(void) 
{
    rTree_t *tree = malloc(sizeof(rTree_t));
    assert(tree);
    tree->prefixLength = 0;
    tree->branchA = NULL; // Bit after prefix is 0
    tree->branchB = NULL; // Bit after prefix is 1
    tree->dataList = NULL;
    return tree;
}

// Locate the longest common prefix between two strings
int longestCommonPrefix(rTree_t *node, char *data)
{
    int counter = 0;
    while (counter <= node->prefixLength && counter <= (strlen(data) + 1) * CHAR_BIT &&
            getBits(node->prefix, counter) == getBits(data, counter))
    {
        counter++;
    }

    return counter; 
}

// Insert a new node into the radix tree
rTree_t* insertData(rTree_t *root, char *data) 
{
    int dataBitCount = (strlen(data) + 1) * CHAR_BIT; // Inclusive of null byte

    // Trivial insertion
    if (root == NULL)
    {
        root = newRadixTree();
        root->prefix = strdup(data);
        root->prefixLength = dataBitCount;
        assert(root);
        return root;
    }

    int commonPrefixLen = longestCommonPrefix(root, data);

    if (longestCommonPrefix == root->prefixLength)
    {
        if (dataBitCount > commonPrefixLen)
        {
            char* rest = splitStem(data, commonPrefixLen + 1, dataBitCount);
            if (getBits(data, commonPrefixLen + 1) == 0)
            {
                insertData(root->branchA, rest);
            }
            else{
                insertData(root->branchB, rest);
            }
        }
        else
        {
            // Duplicate
            
        }
    }

    // 
    char *newRootPrefix = splitStem(root->prefix, 0, commonPrefixLen);
    char *childOnePrefix = splitStem(root->prefix, commonPrefixLen + 1, root->prefixLength);
    char *childTwoPrefix = splitStem(data, commonPrefixLen + 1, dataBitCount);
    
    rTree_t *newRoot = newRadixTree();
    newRoot->prefix = newRootPrefix;
    newRoot->branchA = newRadixTree();
    newRoot->branchB = newRadixTree();
    if (getBits(childOnePrefix, 0) == 0)
    {
        newRoot->branchA->prefix = childOnePrefix;
        newRoot->branchB->prefix = childTwoPrefix;
    }
    else
    {
        newRoot->branchA->prefix = childTwoPrefix;
        newRoot->branchB->prefix = childOnePrefix;
    }

    return newRoot;

}



// Free the radix tree recursively
void freeTree(rTree_t *tree) 
{
    if (tree == NULL) 
    {
        return;
    }
    freeTree(tree->branchA);
    freeTree(tree->branchB);
    freeDynamicCharArray(tree->prefix);
    listFree(tree->dataList, free);
    free(tree);
}