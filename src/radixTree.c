#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "bitWiseOp.h"
#include "data.h"

// Create a new radix tree
rTree_t *newRadixTree(void) 
{
    rTree_t *tree = malloc(sizeof(rTree_t));
    assert(tree);
    tree->prefixLength = 0;
    tree->prefix = NULL;
    tree->branchA = NULL; // Bit after prefix is 0
    tree->branchB = NULL; // Bit after prefix is 1
    tree->dataList = NULL;
    return tree;
}

// Locate the longest common prefix between two strings
int longestCommonPrefix(rTree_t *node, char *data)
{
    char *treePrefix = node->prefix;
    int counter = 0;
    while (getBits(treePrefix, counter) == getBits(data, counter))
    {
        counter++;
    }

    return counter; 
}

// Insert a new node into the radix tree recursively
rTree_t* insertNode(rTree_t *root, void *cafe) 
{   
    cafe_t *data = cafe;
    char *key = strdup(data->tradingName); // Same as split from start to end
    assert(key);
    int keyLength = (strlen(key) + 1) * CHAR_BIT; // In bits null byte inclusive
    int splitKeyAt = 0;
    rTree_t **insertLocation = &root;
    int commonPrefixLen = 0;
    
    while (*insertLocation != NULL)
    {
        commonPrefixLen = longestCommonPrefix(*insertLocation, key);
        splitKeyAt += commonPrefixLen;
        if (splitKeyAt == keyLength)
        {
            // Key already exists
            listAppend((*insertLocation)->dataList, cafe);
            free(key);
            return root;
        }

        if (getBits(key, splitKeyAt) == 0)
        {
            char *oldPrefix = strdup((*insertLocation)->prefix);
            
            // Split prefix from splitKeyAt to prefixLength
            (*insertLocation)->branchB = newRadixTree();
            (*insertLocation)->branchB->prefix = splitStem(oldPrefix, splitKeyAt, (*insertLocation)->prefixLength);
            (*insertLocation)->branchB->prefixLength = (*insertLocation)->prefixLength - splitKeyAt;
            if ((*insertLocation)->dataList != NULL)
            {
                (*insertLocation)->branchB->dataList = (*insertLocation)->dataList;
                (*insertLocation)->dataList = NULL;
            }

            // Update the prefix length
            (*insertLocation)->prefixLength = splitKeyAt;
            (*insertLocation)->prefix = splitStem(oldPrefix, 0, splitKeyAt);
            free(oldPrefix);

            insertLocation = &((*insertLocation)->branchA);
        }
        else
        {
            char *oldPrefix = strdup((*insertLocation)->prefix);
            assert(oldPrefix);
            
            // Split prefix from splitKeyAt to prefixLength
            (*insertLocation)->branchA = newRadixTree();
            (*insertLocation)->branchA->prefix = splitStem(oldPrefix, splitKeyAt, (*insertLocation)->prefixLength);
            (*insertLocation)->branchA->prefixLength = (*insertLocation)->prefixLength - splitKeyAt;

            // Update the prefix length
            (*insertLocation)->prefixLength = splitKeyAt;
            (*insertLocation)->prefix = splitStem(oldPrefix, 0, splitKeyAt);
            free(oldPrefix);

            insertLocation = &((*insertLocation)->branchB);
        }
    }

    // Insert location found insert the prefix and data
    *insertLocation = newRadixTree();
    (*insertLocation)->prefix = splitStem(key, splitKeyAt, keyLength);
    assert((*insertLocation)->prefix);
    (*insertLocation)->prefixLength = keyLength;
    (*insertLocation)->dataList = listCreate();
    listAppend((*insertLocation)->dataList, cafe);
    free(key);
    return root;
}

// Requires bitCmp and charCount to be initialised to 0 before passing in
void searchNode(rTree_t *tree, char *key, int *bitCmp, int *charCount, FILE* outFile)
{
    if (tree == NULL)
    {
        return;
    }

    rTree_t *currentNode = tree;
    rTree_t *previousNode = NULL;
    while (currentNode != NULL)
    {
        // Compare the key with the prefix of the current node until first mismatch
        while (getBits(currentNode->prefix, *bitCmp) == getBits(key, *bitCmp))
        {
            (*bitCmp)++;
            if (*bitCmp != 0 && *bitCmp % CHAR_BIT == 0)
            {
                (*charCount)++;
            }
        }

        // Check if there are extra bits stored in auxillary character
        if (*bitCmp != 0 && *bitCmp % CHAR_BIT != 0)
        {
            (*charCount)++;
        }

        if (getBits(key, *bitCmp) == 0)
        {
            previousNode = currentNode;
            currentNode = currentNode->branchA;
        }
        else
        {
            previousNode = currentNode;
            currentNode = currentNode->branchB;
        }
    }

    printf("--> %s: b%d c%d s1", key, *bitCmp, *charCount);

    // Previous node is the leaf node
    if (previousNode != NULL)
    {
        node_t *current = previousNode->dataList->head;
        fprintf(outFile, "%s\n", key);
        while (current != NULL)
        {
            cafe_t *cafe = current->data;
            printCafe(outFile, cafe);
            current = current->next;
        }
    }
}

// Free the radix tree recursively
void freeTree(rTree_t *tree)
{
    if (tree == NULL)
    {
        return;
    }
    
    if (tree->branchA)
    {
        freeTree(tree->branchA);
    }

    if (tree->branchB)
    {
        freeTree(tree->branchB);
    }

    free(tree->prefix);
    if (tree->dataList)
    {
        listFree(tree->dataList, freeCafe);
    }
    free(tree);
}