#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "data.h"

/* DATA type implementation */

/* Functions Implementation */

// Helper function to assign attributes to cafe
void
assignAttribute(cafe_t *cafe, char *token, int attributeNum)
{
    switch (attributeNum)
    {
        case 0:
            cafe->censusYear = atoi(token);
            return;
        case 1:
            cafe->blockID = atoi(token);
            return;
        case 2:
            cafe->propertyId = atoi(token);
            return;
        case 3:
            cafe->basePropertyId = atoi(token);
            return;
        case 4:
            cafe->buildingAddress = strdup(token);
            return;
        case 5:
            cafe->clueSmallArea = strdup(token);
            return;
        case 6:
            cafe->businessAddress = strdup(token);
            return;
        case 7:
            cafe->tradingName = strdup(token);
            return;
        case 8:
            cafe->industryCode = atoi(token);
            return;
        case 9:
            cafe->industryDescription = strdup(token);
            return;
        case 10:
            cafe->seatingType = strdup(token);
            return;
        case 11:
            cafe->seatCount = atoi(token);
            return;
        case 12:
            cafe->longitude = atof(token);
            return;
        case 13:
            cafe->latitude = atof(token);
            return;
        default:
            return;       
    }
}


// Implement processCsvLine function
void 
processCsvLine(cafe_t *cafe, char *lineBuffer)
{   
    char *token = NULL;
    char *saved = lineBuffer;
    int attributeCase = 0;


    while (*saved != '\0')
    {
        if (*saved != '\"')
        {
            token = strtok_r(NULL, DELIM_COMMA, &saved);
            assignAttribute(cafe, token, attributeCase);
            attributeCase++; 
        }
        else
        {
            saved++; // Skip the starting quptation mark
            token = strtok_r(NULL, DELIM_QUOTE, &saved);
            assignAttribute(cafe, token, attributeCase);
            attributeCase++;
            saved++; // skip the comma after the ending quotation mark
        }
    }
}

// Read csv file into list of cafe
void readCsv(FILE *inFile, list_t *cafes)
{
    // Create a buffer to store each line of the csv file
    char *lineBuffer = NULL;
    size_t bufferSize;

    // discard the first line of csv file
    while (fgetc(inFile) != '\n')
    {
    };
    // Read each line of the csv file
    while (getline(&lineBuffer, &bufferSize, inFile) != -1)
    {
        // Create a new cafe
        cafe_t *cafe = malloc(sizeof(cafe_t));
        assert(cafe);
        // Process the line of csv file
        processCsvLine(cafe, lineBuffer);

        // Add the cafe to the list
        listAppend(cafes, cafe);
    }

    free(lineBuffer); // Free the lineBuffer
}

// Print out the information of cafe into output file
void printCafe(FILE *outFile, cafe_t *cafe)
{
    fprintf(outFile, "--> census_year: %d || ", cafe->censusYear);
    fprintf(outFile, "block_id: %d || ", cafe->blockID);
    fprintf(outFile, "property_id: %d || ", cafe->propertyId);
    fprintf(outFile, "base_property_id: %d || ", cafe->basePropertyId);
    fprintf(outFile, "building_address: %s || ", cafe->buildingAddress);
    fprintf(outFile, "clue_small_area: %s || ", cafe->clueSmallArea);
    fprintf(outFile, "business_address: %s || ", cafe->businessAddress);
    fprintf(outFile, "trading_name: %s || ", cafe->tradingName);
    fprintf(outFile, "industry_code: %d || ", cafe->industryCode);
    fprintf(outFile, "industry_description: %s || ", cafe->industryDescription);
    fprintf(outFile, "seating_type: %s || ", cafe->seatingType);
    fprintf(outFile, "number_of_seats: %d || ", cafe->seatCount);
    fprintf(outFile, "longitude: %lf || ", cafe->longitude);
    fprintf(outFile, "latitude: %lf || \n", cafe->latitude);
}

// Free the memory allocated to individual cafe
void freeCafe(void *data)
{
    cafe_t *cafe = data;
    free(cafe->buildingAddress);
    free(cafe->clueSmallArea);
    free(cafe->businessAddress);
    free(cafe->tradingName);
    free(cafe->industryDescription);
    free(cafe->seatingType);
    free(cafe);
}

// Compare the trading name of two cafes
int compareTradingName(void *data, char key[])
{
    cafe_t *cafe1 = data;
    return strcmp(cafe1->tradingName, key);
}