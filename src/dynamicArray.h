// Define the dynamic array header file
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

/* Include essential libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* Define Constants */
#define NOT_FOUND -1
#define INITIAL_SIZE 2
/* Define data types */
typedef struct dynamicArray dynamicArray_t;
struct dynamicArray 
{
    char **array;
    size_t size;
    size_t elementCount;
};

/* Dynamic array specific functions */
// Create a new dynamic char array
dynamicArray_t *createDynamicArray(void);

// Ensure that the dynamic char array has enough space for new char
void ensureArrayCapacity(dynamicArray_t *dArray);

// Insert new char into the dynamic char array
void insertData(dynamicArray_t *dArray, char* data);

// Shrink the dynamic char array for memory efficiency
void shrinkArray(dynamicArray_t *dArray);

// Free the dynamic char array
void freeDynamicArray(dynamicArray_t *dArray);

// Find the first match then linear search around it for rest of matches
int findAndTraverse(dynamicArray_t *dArray, char *key, 
        int (*compare)(char *, char *, int *), int *leftMatches, int *rightMatches, 
        int *strCmpCount, int *charCmpCount);

// Determine if a key has already been searched for
int isSearched(char *key, dynamicArray_t *dArray);

#endif