#ifndef DYNAMICSTRING_H
#define DYNAMICSTRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Constant Def
#define INITIAL_CAPACITY 2

/* Data type definition */
typedef struct dynamicString dynamicString_t;
struct dynamicString 
{
    char *string;
    int length; // Ixclusive of null terminator
    int capacity;
};

// Function prototypes
dynamicString_t *createDynamicString();
void freeDynamicString(dynamicString_t *string);
void ensureCapacity(dynamicString_t *string);
void shrinkCapacity(dynamicString_t *string);
void appendDynamicString(dynamicString_t *string, char character);

#endif 