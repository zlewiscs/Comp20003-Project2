/* Define the header file */
#ifndef BITWISEOP_H
#define BITWISEOP_H

/* Include essential libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* >>>>>>>>>>>>>>>>>>>> Define constants*/
#define CHAR_BIT 8

/* >>>>>>>>>>>>>>>>>>>> Function Prototypes*/
// get the number of bits of a given character
int getBits(const char *key, int n);

// Extract (end - start) number of bits from the key
char* splitStem(char key, int start, int end);

/* End of header file */
#endif