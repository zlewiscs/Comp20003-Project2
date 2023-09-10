#ifndef DATA_H
#define DATA_H

/* include essential header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "dynamicArray.h"
#include "radixTree.h"

/* Define Constants */
#define MAX_STRLEN 128
#define DECI_PLACE 5
#define ATTRIBUTE_COUNT 14
#define DELIM_COMMA ","
#define DELIM_QUOTE "\""
#define MAX_LINE 512

/*  Define data types */
typedef struct cafe cafe_t;
struct cafe
{
    int censusYear; // case 0
    int blockID; // case 1
    int propertyId; // case 2
    int basePropertyId; // case 3
    char *buildingAddress; // case 4 
    char *clueSmallArea; // case 5
    char *businessAddress; // case 6
    char *tradingName; // case 7
    int industryCode; // case 8
    char *industryDescription; // case 9
    char *seatingType; // case 10
    int seatCount; // case 11
    double longitude; // case 12
    double latitude; // case 13
};

/* Define Function Prototypes */
// Process each line of csv file.
void processCsvLine(cafe_t *cafe, char *lineBuffer);

// Helper function to assign attributes to cafe.
void assignAttribute(cafe_t *cafe, char *token, int attributeNum);

// Read csv data into list.
void readCsv(FILE *inFile, list_t *cafes, dynamicArray_t *tradingNames, rTree_t *radixTree);

// Print cafe data to file.
void printCafe(FILE *outFile, cafe_t *cafe);

// Free the memory allocated to individual cafe.
void freeCafe(void *data);

// Compare the trading name of two cafes
int compareTradingName(void *data, char key[]);

// Compare partial trading name with trading name of cafe
int comparePartialTradingName(char *target, char *key, int *charCmpCount);

// Custom strcmp function that counts the number of character comparisons
int strncmpWithCount(char *target, char *key, size_t n, int *charCount);

// Strcmp wrapper for qsort
int strcmpWrapper(const void *key1, const void *key2);

// Small range hence insertion sort will be better
void sortCafes(void* array, int dataCount);

//

#endif /* DATA_H */
