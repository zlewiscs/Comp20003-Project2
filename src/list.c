#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t *listCreate()
{
    list_t *list = malloc(sizeof(*list));
    assert(list);
    list->head = list->tail = NULL;
    list->elementCount = 0;
    return list;
}

void listFree(list_t *list, void (*dataFree)(void *))
{
    assert(list != NULL);
    node_t *curr = list->head; // curr points to the first node
    while (curr)
    { // While curr not reaching the end of list
        node_t *tmp = curr;
        curr = curr->next;   // Advance curr to the next next node
        dataFree(tmp->data); // Frees the previous node including
        free(tmp);           //    Freeing the space used by data
    }
    free(list); // Free the list itself
}

void listPrepend(list_t *list, void *data)
{
    assert(list);

    // Creates a new node and set data stored to given data value
    node_t *new = malloc(sizeof(*new));
    assert(new);
    new->data = data;

    // Links the new node to the list
    new->next = list->head; // Connects "new" to the head node
    list->head = new;       // Repairs the pointer "head"

    // Checks special initial condition of inserting into an empty list
    if (list->tail == NULL)
    {                     // Original list is empty
        list->tail = new; // So "new" is also the tail node
    }
    // Updates the number of elements in the list
    (list->elementCount)++;
}
void listAppend(list_t *list, void *data)
{
    assert(list);

    // Creates a new node and set data to provided value
    node_t *new = malloc(sizeof(*new));
    assert(new);
    new->data = data;
    new->next = NULL; // "new" is the last node
    if (list->tail != NULL)
    {
        list->tail->next = new; // Only change the next pointer of the old tail node if it exists
    }
    if (list->head == NULL)
    {                     // Original list is empty
        list->head = new; // So "new" is also the head node
    }
    list->tail = new; // "new" is the new tail node
    (list->elementCount)++;
}
int listSearch(list_t *list, char key[], void *data[], int (*comparator)(void *, char *))
{
    assert(list);
    int matches = 0;
    node_t *curr = list->head; // curr points to the first node
                               // curr points to the first node
    while (curr)
    { // While curr not reaching the end of list
        if (comparator(curr->data, key) == 0)
        { // Found the data
            data[matches] = curr->data;
            matches++;
        }
        curr = curr->next; // Advance curr to the next next node
    }
    return matches; // Return the number of matches
}
