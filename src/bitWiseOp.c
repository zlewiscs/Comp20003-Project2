/* Include essential libries and headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "bitWiseOp.h"

/* >>>>>>>>>>>>>>>>>>>>>>>>>>> Function Implementations */
// Obtain the nth bit of key.
int getBits(char key, int n) {
    int bit = (key >> n) & 1;
    return bit;
}

unsigned int splitStem(const char *key, int start, int end) {
    
}