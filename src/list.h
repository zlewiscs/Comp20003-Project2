#ifndef LIST_H
#define LIST_H

// INCLUDES libraries
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// TYPE DEFINITIONS

// A node in the linked list
typedef struct node node_t;
struct node
{
    void *data;
    node_t *next;
};

// The linked list
struct list
{
    node_t *head;
    node_t *tail;
    int elementCount;
};
typedef struct list list_t;

// FUNCTION PROTOTYPES

// Creates & returns an empty linked list
list_t *listCreate();

// Free the list, with the help of function "freeData" for freeing the data component
void listFree(list_t *list, void (*dataFree)(void *));

// Returns 1 if the list is empty, 0 otherwise
int listIsEmpty(list_t *list);

// Functions for insertion >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// Inserts a new node with value "data" to the front of "list"
void listPrepend(list_t *list, void *data);

// Inserts a new node with value "data" to the end of "list"
void listAppend(list_t *list, void *data);

// Performs linear search in "list", returns found data or NULL
// Here we assume that key is an int (a limited assumption for sake of simplicity!)
int listSearch(list_t *list, char key[], void *data[], int (*comparator)(void *, char *));

#endif
