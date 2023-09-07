#include "bitWiseOp.h"

// Get the bit value of a characture at position n
int getBits(const char *key, int n) 
{
    /* Get the position of the character in the string
     * 0 meaning the first character , 2 meaning the second
     * by floor division by size of a single char in bits 
    */ 
    int position = n / CHAR_BIT;

    // Get the bit position of the character in the string
    int bitPosition = n % CHAR_BIT;

    // Right shift the desired bit to the rightmost position and masked by 0b1
    return (key[position] >> (CHAR_BIT- bitPosition - 1)) & 0b1;
}

// Extract (end - start) number of bits from the stem (a string)
char* splitStem(char* stem, int start, int end) 
{

    // Get the length of the stem to be extracted
    int length = (end - start) + (start % CHAR_BIT) + 1; // Bits
    int stringLength = length / CHAR_BIT + 1; // Characters

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

    // Generate a mask for the last non null terminating character
    char mask = (0b11111111 - ((0b1 << ((stringLength * CHAR_BIT - end) % CHAR_BIT)) - 1));

    for(int i = 0; i < 8; i++) {printf("%d", getBits(&mask, i));}

    // Left shift 1 to the end'th binary bit then subtract 1 to mask the last char
    extractedStem[stringLength - 1] &= mask;

    // Append null terminator
    extractedStem[stringLength] = '\0';

    return extractedStem;

}
