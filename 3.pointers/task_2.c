#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../lib/dataStructures/list.h"

#define DELETE_COMMAND "DELETE"
#define INSERT_COMMAND "INSERT"
#define REPLACE_COMMAND "REPLACE"

#define MAX_SEQUENCE_LENGTH 128

enum Command {
    Delete,
    Insert,
    Replace,
    Unknown
};

String pchar2string(const char* c) { return stringPush(stringDup(""), *c); }
char pchar2char(const char* c) { return *c; }
bool pcharcmp(const char* c1, const char* c2) {return *c1 == *c2;}

char* pcharcpy(const char* c)
{
    char* new = malloc(sizeof(char));
    *new = *c;
    return new;
}

void readSeqToList(List sequence, FILE* inputStream)
{
    char buffer[MAX_SEQUENCE_LENGTH] = "";
    fscanf(inputStream, "%s", buffer);

    for (int i = 0; i < strlen(buffer); i++) {
        char* c1 = malloc(sizeof(char));
        *c1 = buffer[i];
        listPushback(sequence, c1);
    }
}

String readCmd(FILE* inputStream)
{
    List cmd = listCreate();
    readSeqToList(cmd, inputStream);
    String res = listToString(cmd, (char(*)(void*))pchar2char);
    listFree(cmd);

    return res;
}

size_t identifyCmd(String command)
{
    size_t commandType = Unknown;

    String delCommand = stringDup(DELETE_COMMAND);
    String insCommand = stringDup(INSERT_COMMAND);
    String replCommand = stringDup(REPLACE_COMMAND);

    if (stringCmp(command, delCommand) == 0)
        commandType = Delete;
    else if (stringCmp(command, insCommand) == 0)
        commandType = Insert;
    else if (stringCmp(command, replCommand) == 0)
        commandType = Replace;

    stringFree(delCommand);
    stringFree(insCommand);
    stringFree(replCommand);

    return commandType;
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

    FILE* inputFile = fopen(inputFilePath, "r");
    FILE* outputFile = fopen(outputFilePath, "w");

    int sequenceLength = 0;
    fscanf(inputFile, "%d", &sequenceLength);

    List sequence = listCreate();
    readSeqToList(sequence, inputFile);
    listPrint(sequence, (String(*)(void*))pchar2string, NULL, outputFile);
    fprintf(outputFile, "\n");

    int operationsLength = 0;
    fscanf(inputFile, "%d", &operationsLength);

    for (int i = 0; i < operationsLength; i++) {
        String command = readCmd(inputFile);
        size_t commandType = identifyCmd(command);
        stringFree(command);

        List first = listCreate();
        readSeqToList(first, inputFile);
        List second = listCreate();
        readSeqToList(second, inputFile);

        printf("%d\n", i);
        switch (commandType) {
        case Delete:
            if (!listDeleteFromToSeqs(sequence, first, second, pcharcmp)) {
                printf("Error deleting");
                exit(0);
            }
            break;
        case Insert:
            if (!listInsertSeqAfterSeq(sequence, first, second, pcharcmp, pcharcpy)) {
                printf("Error inserting");
                exit(0);
            }
            break;
        case Replace:
            if (!listReplace(sequence, first, second, pcharcmp, pcharcpy)) {
                printf("Error replacing");
                exit(0);
            }
            break;
        case Unknown:
            printf("Error: unknown command");
            exit(0);
        }

        listPrint(sequence, (String(*)(void*))pchar2string, NULL, outputFile);
        fprintf(outputFile, "\n");

        listFree(first);
        listFree(second);
    }

    listFree(sequence);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
