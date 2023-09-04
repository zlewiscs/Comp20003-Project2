#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int main(int argc, char **argv) {
    // test splitStem function
    char *key = "aaaa";
    char *key0 = "aaaaa";
    int charCount = 0;
    printf("%d", strcmpWithCount(key, key0, &charCount));
    printf("\n");
    printf("%d", charCount);
    printf("\n");
    return 0;
}

