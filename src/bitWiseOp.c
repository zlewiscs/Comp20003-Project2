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
    int length = end - start; // Bits
    if (length <= 0)
    {
        return NULL;
    }
    int stringLength = length / CHAR_BIT + 1; // Characters

    // Allocate memory for the extracted stem
    char* extractedStem = (char*) calloc(sizeof(char) * (stringLength + 1), sizeof(char));
    assert(extractedStem);

    int currBit = 0;

    for (int i = start; i < length; i++)
    {
        int bit = getBits(stem, i);
        // Current bit mod char bit is to ensure leftshift num is always between 0 and 8 exclusive
        extractedStem[currBit / CHAR_BIT] |= (bit << (CHAR_BIT - 1 - (currBit % CHAR_BIT)));
        currBit++;
    }

    return extractedStem;

}