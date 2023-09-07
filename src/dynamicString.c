#include "dynamicString.h"

// Function to create a new dynamic string
dynamicString_t *createDynamicString() 
{
    dynamicString_t *string = malloc(sizeof(dynamicString_t));
    assert(string);
    string->string = malloc(INITIAL_CAPACITY * sizeof(char));
    assert(string->string != NULL);
    string->length = 0;
    string->capacity = INITIAL_CAPACITY;
    return string;
}

// Function to free a dynamic string
void freeDynamicString(dynamicString_t *string) 
{
    assert(string);
    free(string->string);
    free(string);
}

// Function to ensure capacity of a dynamic string
void ensureCapacity(dynamicString_t *string) 
{
    assert(string);
    if (string->length == string->capacity) 
    {
        string->capacity *= 2;
        string->string = realloc(string->string, string->capacity * sizeof(char));
        assert(string->string != NULL);
    }
}

// Function to shrink capacity of a dynamic string
void shrinkCapacity(dynamicString_t *string) 
{
    assert(string);
    if (string->length < string->capacity) 
    {
        string->capacity = string->length;
        string->string = realloc(string->string, string->capacity * sizeof(char));
        assert(string->string != NULL);
    }
}

// Function to append a character to a dynamic string
void appendDynamicString(dynamicString_t *string, char character) 
{
    assert(string);
    ensureCapacity(string);
    string->string[string->length] = character;
    string->length++;
    string->string[string->length] = '\0';
    string->length++; // Ensure null terminator is included in length

}