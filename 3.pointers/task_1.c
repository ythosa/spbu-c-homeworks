#include <stdio.h>
#include <unistd.h>

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
            ++*value;
            dictPut(words, key, value);
        } else {
            value = malloc(sizeof(int));
            *value = 1;
            dictPut(words, key, value);
        }
    }
}

String dictValueFormatter(const int* v)
{
    char str[64];
    sprintf(str, "%d", *v);

    return stringDup(str);
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("invalid count of arguments. please provide "
               "inputFile file path and outputFile file path through space");
    }

    char* inputFilePath = argv[1];
    if (access(inputFilePath, F_OK) != 0) {
        printf("error: file: %s doesn't exists", inputFilePath);

        return 0;
    }

    char* outputFilePath = argv[2];
    if (access(outputFilePath, F_OK) != 0) {
        printf("error: file: %s doesn't exists", outputFilePath);

        return 0;
    }

    Dict words = dictCreate(free);

    FILE* inputFile = fopen(inputFilePath, "r");
    readWordsToDict(inputFile, words);
    fclose(inputFile);

    FILE* outputFile = fopen(outputFilePath, "w");
    csvPrintDict(words, (String(*)(void*))dictValueFormatter, outputFile);
    fclose(outputFile);

    dictFree(words, free);

    return 0;
}
