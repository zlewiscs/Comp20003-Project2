#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "list.h"
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

  // read in the csv file
  readCsv(inFile, cafes);

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

  // free key
  free(key);

  // print out the element count
  //  free list
  listFree(cafes, freeCafe);

  // close files
  fclose(inFile);
  fclose(outFile);

  return 0;
}
