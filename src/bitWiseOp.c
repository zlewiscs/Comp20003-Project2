#include "bitWiseOp.h"

// Get the bit value of a characture at position n
char getBits(const char key, int n) {
    // assert(n >= 0 && n <= 7);
    assert(n <= 7);

    /* 
    Right shift the desired bit to the least significant
    position (aka right most) and then perform a bitwise AND with 1
    */
    return ((key >> n) & 1) + '0';
}

// Extract (end - start) number of bits from the key
char* splitStem(const char key, int start, int end) {
    // Ensure start and end are reasonable
    assert(start >= 0 && start < CHAR_BIT);
    assert(end >= 0 && end < CHAR_BIT);
    assert(start <= end);

    // Calculate the length of the field to be extracted
    int length = end - start + 1;
    // Initiate the result
    char *result = malloc(sizeof(char) * length);
    assert(result);
    // Extract the field
    for (int i = 0; i < length; i++) {
        result[i] = getBits(key, start + i); 
    }

    return result;
}