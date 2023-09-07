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
		
		// To store keys already searched for
		dynamicArray_t *keys = createDynamicArray();
		// To store printedKeys to prevent further printing
		dynamicArray_t *printedKeys = createDynamicArray();
		
		/*
		**First binary search for first match and then
		**linear search around the first match 
		**for all other cafes with matching trading name prefix
		*/ 
		while (getline(&key, &len, stdin) != -1)
		{
			// Insert the key into the keys dynamic array
			insertData(keys, key);

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
					if (i > 0 && strncmp(tradingNames->array[i], tradingNames->array[i - 1], strlen(key)) == 0)
					{
						continue;
					}

					int bitCount = charCmpCount * 8;
					
					printf("%s --> b%d c%d s%d\n", 
					tradingNames->array[i], bitCount, charCmpCount, strCmpCount);

					// Search for cafes with matching trading name in the list
					void *matches[cafes->elementCount];
					int matchCount = listSearch(cafes, tradingNames->array[i], matches, compareTradingName);
					for (int j = 0; j < matchCount; j++)
					{
						cafe_t *cafe = matches[j];
						if (isSearched(key, printedKeys) == 0)
						{
							fprintf(outFile, "%s\n", key);
							insertData(printedKeys, key);
						}
						printCafe(outFile, cafe);

					}
				}
			}
		}
		// Free printedKeys
		freeDynamicArray(printedKeys);

		freeDynamicArray(keys);
	}
	else if (stage == 3)
	{
		// Create a radix tree
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