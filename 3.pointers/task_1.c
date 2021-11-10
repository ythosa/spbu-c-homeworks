#include <stdio.h>

#include "../lib/dataStructures/dict.h"
#include "../lib/io/csv.h"

#define MAX_WORD_LENGTH 128

void readWordsToDict(FILE* inputStream, Dict words)
{
    char buffer[MAX_WORD_LENGTH] = "";
    while (fscanf(inputStream, "%s", buffer) != EOF) {
        String key = stringDup(buffer);
        int* value = (int*)dictGet(words, key);
        if (value) {
            ++(*value);
            stringFree(key);
        } else {
            value = malloc(sizeof(int));
            *value = 1;
            dictPut(words, key, value);
        }
    }
}

String dictValueFormatter(const int* v)
{
    char str[64] = "";
    sprintf(str, "%d", *v);

    return stringDup(str);
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("invalid count of arguments. please provide "
               "inputFile file path and outputFile file path through space\n");

        return 0;
    }

    char* inputFilePath = argv[1];
    char* outputFilePath = argv[2];

    Dict words = dictCreate(free);

    FILE* inputFile = fopen(inputFilePath, "r");
    if (!inputFile) {
        printf("invalid input file path: %s\n", inputFilePath);

        return 0;
    }

    readWordsToDict(inputFile, words);
    fclose(inputFile);

    FILE* outputFile = fopen(outputFilePath, "w");
    csvPrintDict(words, (String(*)(void*))dictValueFormatter, outputFile);
    fclose(outputFile);

    dictFree(words);

    return 0;
}
