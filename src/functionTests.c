#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CHAR_BIT 8

// Get the bit value of a characture at position n
char getBits(const char key, int n) 
{
    // assert(n >= 0 && n <= 7);
    assert(n <= 7);

    /* 
    Right shift the desired bit to the least significant
    position (aka right most) and then perform a bitwise AND with 1
    */
    return ((key >> (n - 1)) & 1) + '0';
}

// Extract (end - start) number of bits from the key
char splitStem(const char key, int start, int end) 
{
    // Ensure start and end are reasonable
    assert(start >= 0 && start < CHAR_BIT);
    assert(end >= 0 && end < CHAR_BIT);
    assert(start <= end);

    // Calculate the length of the field to be extracted
    int length = end - start;
    // Initiate the result
    char result = key;

    // Left shift key by length to get the desired bits to the most significant position
    result = (result << length) - 1;

    return (key & result);
}

int main(int argc, char **argv) 
{
    // See the logic
    char A = 0b01000001;
    printf("A in binary: ");
    for(int i = 0; i < 8; i++) {printf("%c", getBits(A, i));}
    printf("\n");

    char A1 = (A << 1);
    printf("A in binary after left shift by 3: ");
    for(int i = 0; i < 8; i++) {printf("%c", getBits(A1, i));}
    printf("\n");

    char mask = A1 - 1;
    printf("mask for 1 bit in binary: ");
    for(int i = 0; i < 8; i++) {printf("%c", getBits(mask, i));}
    printf("\n");

    char A2 = A & mask;
    printf("A in binary after masking: ");
    for(int i = 0; i < 8; i++) {printf("%c", getBits(A2, i));}
    printf("\n");

    // Test splitStem function
    char A3 = splitStem(A, 0, 1);
    printf("A in binary after splitStem: ");
    for(int i = 0; i < 8; i++) {printf("%c", getBits(A3, i));}
    printf("\n");

    printf("Char A after splitStem: %c\n", A3);
    
    return 0;
}

