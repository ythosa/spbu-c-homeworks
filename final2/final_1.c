#include "../lib/treemap/treemap.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAX_WORD_LENGTH 32

void readWordsFromFileToTreeMap(FILE* inputStream, TreeMap* map)
{
    char wordBuffer[MAX_WORD_LENGTH] = "";

    while (fscanf(inputStream, "%s", wordBuffer) != EOF) {
        if (!treeMapHasKey(map, wrapString(wordBuffer))) {
            char* word = calloc(strlen(wordBuffer) + 1, sizeof(char));
            strcpy(word, wordBuffer);
            treeMapPut(map, wrapString(word), wrapNone());
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("You need to provide input file path and output file path in args!\n");

        return 0;
    }

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        printf("Invalid input file path!\n");

        return 0;
    }

    TreeMap* map = treeMapCreate(compare);
    
    readWordsFromFileToTreeMap(inputFile, map);
    fclose(inputFile);

    FILE* outputFile = fopen(argv[2], "w");
    TreeMapIterator* treeMapIterator = treeMapIteratorCreate(map);
    while (treeMapIteratorHasElement(treeMapIterator)) {
        char* word = getString(nodeGetKey(treeMapIteratorGetNext(treeMapIterator)));
        fprintf(outputFile, "%s ", word);
        free(word);
    }
    treeMapIteratorFree(treeMapIterator);
    fclose(outputFile);

    treeMapFree(map);

    return 0;
}
