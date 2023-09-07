#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CHAR_BIT 8

// Get the bit value of a characture at position n
int getBits(const char *key, int n) {
    /* Get the position of the character in the string
     * 0 meaning the first character , 2 meaning the second
     * by floor division by size of a single char in bits 
    */ 
    int position = n / CHAR_BIT;

    // Get the bit position of the character in the string
    int bitPosition = n % CHAR_BIT;

    return (key[position] >> (CHAR_BIT- bitPosition - 1)) & 0b1;
}

// Extract (end - start) number of bits from the stem (a string)
char* splitStem(char* stem, int start, int end) 
{
    printf("strlen of stem: %ld\n", strlen(stem));
    printf("# of bits stored by stem: %ld\n", strlen(stem) * CHAR_BIT);
    // Get the length of the stem to be extracted
    int length = (end - start) + (start % CHAR_BIT) + 1; // Bits
    printf("start at: %d\n", start);
    printf("end at: %d\n", end);
    printf("Length: %d\n", length);
    int stringLength = length / CHAR_BIT + 1; // Characters
    printf("String length: %d\n", stringLength);

    // Allocate memory for the extracted stem
    char* extractedStem = (char*) malloc(sizeof(char) * (stringLength + 1));
    assert(extractedStem);

    // Locate the character storing the first bit to be extracted
    int startChar = start / CHAR_BIT; // 0 -> 0, 1 -> 0, 7 -> 0, 8 -> 1, 9 -> 1, 15 -> 1, 16 -> 2, 17 -> 2 ...
    int startBit = start % CHAR_BIT; // 0 -> 0, 1 -> 1, 7 -> 7, 8 -> 0, 9 -> 1, 15 -> 7, 16 -> 0, 17 -> 1 ...
    // Mask the starting character and append it to 0th position of character string
    extractedStem[0] = stem[startChar] & ((0b1 << (CHAR_BIT - startBit)) - 1);

    // Fill in the rest of the characters to extractedStem until the end
    for (int i = 1; i < stringLength; i++) 
    {
        extractedStem[i] = stem[startChar + i];
    }
    char mask = (0b11111111 - ((0b1 << ((stringLength * CHAR_BIT - end) % CHAR_BIT)) - 1));
    printf("Mask for last char:\n");
    for(int i = 0; i < 8; i++) {printf("%d", getBits(&mask, i));}
    printf("\n");
    // Left shift 1 to the end'th binary bit then subtract 1 to mask the last char
    extractedStem[stringLength - 1] &= mask;
    printf("Last character in binary for extracted stem:\n");
    for (int i = 0; i < CHAR_BIT; i++) {printf("%d", getBits(&extractedStem[stringLength - 1], i));}
    printf("\n");

    // Append null terminator
    extractedStem[stringLength] = '\0';

    return extractedStem;

}

int main(int argc, char **argv) 
{
    // Test getbits
    char *key = "Domino's Pizza\0";
    char *secondKey = "Arbory Bar and Eatery\0";
    for (int i = 0; i < strlen(key) * CHAR_BIT; i++) 
    {
        if(i % 8 == 0 && i > 0) {printf(" ");}
            
        printf("%d", getBits(key, i));
    }
    printf("\n");
    for (int i = 0; i < strlen(secondKey) * CHAR_BIT; i++) 
    {
        if(i % 8 == 0 && i > 0) {printf(" ");}
            
        printf("%d", getBits(secondKey, i));
    }
    printf("\n");

    // Test splitStem
    char *test = splitStem(key, 12, ((strlen(key)) * CHAR_BIT) - 32);
    printf("Should end at: %ld\n", ((strlen(key)) * CHAR_BIT) - 32);
    printf("Extracted stem:\n");
    for (int i = 0; i < (strlen(test) + 1) * CHAR_BIT; i++) 
    {
        if(i % 8 == 0 && i > 0) {printf(" ");}
        printf("%d", getBits(test, i));
    }
    printf("\n");

    return 0;
}

