#include "dynamicArray.h"

// Create dynamic array
dynamicArray_t *createDynamicArray(void) 
{
    dynamicArray_t *dArray = malloc(sizeof(dynamicArray_t));
    assert(dArray);
    dArray->size = INITIAL_SIZE;
    dArray->array = malloc(sizeof(*(dArray->array)) * dArray->size);
    assert(dArray->array);
    dArray->elementCount = 0;
    return dArray;
}

// Ensure that the dynamic char array has enough space for new char
void ensureArrayCapacity(dynamicArray_t *dArray) 
{
    if (dArray->elementCount == dArray->size)
    {
        dArray->size *= 2;
        dArray->array = realloc(dArray->array, sizeof(*(dArray->array)) * dArray->size);
        assert(dArray->array);
    }
    
}

// Insert new data into dynamic array
void insertData(dynamicArray_t *dArray, char *data) 
{
    ensureArrayCapacity(dArray);
    // Allocate memory for and copy the new data
    dArray->array[dArray->elementCount] = strdup(data);
    assert(dArray->array[dArray->elementCount]);

    // Increment the element count
    (dArray->elementCount) += 1;
}

// Shrink the dynamic char array for memory efficiency
void shrinkArray(dynamicArray_t *dArray) 
{
    if (dArray->elementCount < dArray->size)
    {
        if (dArray->elementCount < INITIAL_SIZE)
        {
            dArray->size = INITIAL_SIZE;
        }
        else
        {
            dArray->size = dArray->elementCount;
            
        }
        dArray->array = realloc(dArray->array, sizeof(*(dArray->array)) * dArray->size);
        assert(dArray->array);
    }
}

// Free the memory allocated to the dynamic array and the data
void freeDynamicArray(dynamicArray_t *dArray) 
{
    for (int i = 0; i < dArray->elementCount; i++) {
        free(dArray->array[i]);
    }
    free(dArray->array);
    free(dArray);
}

// binary search
int binarySearch(dynamicArray_t *dArray, char* key, int (*compare)(char *, char *, int*), 
    int *strCmpCount, int *charCmpCount) 
{
    int low = 0;
    int high = dArray->elementCount - 1;
    int mid;

    // Iteratively implement binary search
    while (low <= high) 
    {
        mid = (low + high) / 2;
        int cmpResult = compare(dArray->array[mid], key, charCmpCount);
        *strCmpCount+= 1;
        if (cmpResult == 0) 
        {
            return mid;
        }
        else if (cmpResult < 0) 
        {
            low = mid + 1;
        }
        else 
        {
            high = mid - 1;
        }
    }
    return NOT_FOUND; // Not found
}

// Find the first match then linear search around it for rest of matches
int findAndTraverse(dynamicArray_t *dArray, char *key, 
        int (*compare)(char *, char *, int*), int *leftMatches, int *rightMatches, 
        int *strCmpCount, int *charCmpCount) 
{

    // Binary search for first match
    int firstMatch = binarySearch(dArray, key, compare, strCmpCount, charCmpCount);
    *leftMatches = *rightMatches = firstMatch;
    if (firstMatch == NOT_FOUND) 
    {
        return NOT_FOUND;
    }
    else 
    {
        if (firstMatch > 0) 
        {
            // Linear search left
            for (int i = firstMatch - 1; i >= 0; i--) 
            {
                int cmpResult = compare(dArray->array[i], key, charCmpCount);
                *strCmpCount+= 1;
                if (cmpResult == 0) 
                {
                    *leftMatches = i;
                }
                else 
                {
                    break;
                }
            }
        }

        if (firstMatch < dArray->elementCount - 1) 
        {
            // Linear search right
            for (int i = firstMatch + 1; i < dArray->elementCount; i++) 
            {
                int cmpResult = compare(dArray->array[i], key, charCmpCount);
                *strCmpCount+= 1;
                if (cmpResult == 0) 
                {
                    *rightMatches = i;
                }
                else 
                {
                    break;
                }
            }
        }
    }

    return firstMatch;   
}