#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "list.h"
#include "dynamicArray.h"
int main(int argc, char **argv)
{
	// get stage
	int stage = atoi(argv[1]);
	// open input file
	FILE *inFile = fopen(argv[2], "r");
	assert(inFile);
	// open output file
	FILE *outFile = fopen(argv[3], "w");
	assert(outFile);

	// read in extra lines from stdin using getline()
	char *key = NULL;
	size_t len = 0;

	// create a list of cafes
	list_t *cafes = listCreate();

	// Create a dynamic array of trading names
	dynamicArray_t *tradingNames = createDynamicArray();

	// read in the csv file
	readCsv(inFile, cafes, tradingNames);
	shrinkArray(tradingNames);

	// The following is stage 1
	if (stage == 1) {
		// search for cafes with matching trading name
		while (getline(&key, &len, stdin) != -1)
		{
			// remove the newline character
			key[strlen(key) - 1] = '\0';

			// create array of matches
			void *matches[cafes->elementCount];
			int matchCount = listSearch(cafes, key, matches, compareTradingName);
			if (matchCount == 0)
			{
				printf("%s --> NOTFOUND\n", key);
			}
			else
			{
				printf("%s --> %i\n", key, matchCount);
			}
			fprintf(outFile, "%s\n", key);
			for (int i = 0; i < matchCount; i++)
			{
				cafe_t *cafe = matches[i];
				printCafe(outFile, cafe);
			}
		}
	}
	
    else if (stage == 2)
	{
		// Sort the tradingNames dynamic array
		qsort(tradingNames->array, tradingNames->elementCount, 
				sizeof(char *), strcmpWrapper);
		
		/*
		**First binary search for first match and then
		**linear search around the first match 
		**for all other cafes with matching trading name prefix
		*/ 
		while (getline(&key, &len, stdin) != -1)
		{
			// For each new line reset the comparison counts
			// Variable to store the number of comparison made
			int strCmpCount = 0;
			int charCmpCount = 0;

			// remove the newline character
			key[strlen(key) - 1] = '\0';

			// Variable to store the range of matches in the dynamic array
			int leftMatches = 0;
			int rightMatches = 0;

			// Find the first match then linear search around it for rest of matches
			int firstMatch = findAndTraverse(tradingNames, key, comparePartialTradingName, 
							&leftMatches, &rightMatches, &strCmpCount, &charCmpCount);
			
			// Print out the result, do nothing is no match is found
			if (firstMatch != -1) 
			{
				for (int i = leftMatches; i <= rightMatches; i++) 
				{
					int bitCount = charCmpCount * 8;
					fprintf(outFile, "%s --> b%d, c%d, s%d\n", 
					tradingNames->array[i], bitCount, charCmpCount, strCmpCount);
				}
				
			}
		}

	}

	// free key
	free(key);

	//  free list
	listFree(cafes, freeCafe);

	// free dynamic array
	freeDynamicArray(tradingNames);

	// close files
	fclose(inFile);
	fclose(outFile);

	return 0;
}

