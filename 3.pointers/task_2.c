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
#define MAX_COMMAND_LENGTH 16

enum Command {
    Delete,
    Insert,
    Replace,
    Unknown,
};

void readSequenceToList(List sequence, FILE* inputStream)
{
    char buffer[MAX_SEQUENCE_LENGTH] = "";
    fscanf(inputStream, "%s", buffer);

    for (int i = 0; i < strlen(buffer); i++) {
        char* c1 = malloc(sizeof(char));
        *c1 = buffer[i];
        listPushBack(sequence, c1);
    }
}

String listCharElementToString(const char* c)
{
    return stringPushChar(stringDup(""), *c);
}

char listCharElementToChar(const char* c)
{
    return *c;
}

char* listCopyCharElement(const char* c)
{
    char* new = malloc(sizeof(char));
    *new = *c;

    return new;
}

bool comparator(const char* c1, const char* c2) {
    return *c1 == *c2;
}

String readCommand(FILE* inputStream)
{
    char buffer[MAX_COMMAND_LENGTH] = "";
    fscanf(inputStream, "%s", buffer);

    List commandList = listCreate();
    for (int i = 0; i < strlen(buffer); i++) {
        char* c1 = malloc(sizeof(char));
        *c1 = buffer[i];
        listPushBack(commandList, c1);
    }
    String command = listToString(commandList, (char(*)(void*))listCharElementToChar);
    listFree(commandList);

    return command;
}

size_t identifyCommandType(String command)
{
    size_t commandType = Unknown;

    String deleteCommand = stringDup(DELETE_COMMAND);
    String insertCommand = stringDup(INSERT_COMMAND);
    String replaceCommand = stringDup(REPLACE_COMMAND);

    if (stringCompare(command, deleteCommand) == 0) {
        commandType = Delete;
        goto free;
    }

    if (stringCompare(command, insertCommand) == 0) {
        commandType = Insert;
        goto free;
    }

    if (stringCompare(command, replaceCommand) == 0) {
        commandType = Replace;
        goto free;
    }

free:
    stringFree(deleteCommand);
    stringFree(insertCommand);
    stringFree(replaceCommand);

    return commandType;
}

//int main() {
//    List l = listCreate();
//    char a = 'a';
//    char b = 'b';
//    char c = 'c';
//    listPushBack(l, &a);
//    listPushBack(l, &b);
//    listPushBack(l, &c);
//
//    listPrint(l, listCharElementToString, NULL, stdout);
//
//    List new = listCopy(l, listCopyCharElement);
//    listPrint(new, listCharElementToString, NULL, stdout);
//
//    return 0;
//}

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

    int sequenceLength = 0;
    fscanf(inputFile, "%d", &sequenceLength);

    List sequence = listCreate();
    readSequenceToList(sequence, inputFile);

    int operationsLength = 0;
    fscanf(inputFile, "%d", &operationsLength);

    for (int i = 0; i < 1; i++) {
        String command = readCommand(inputFile);
        size_t commandType = identifyCommandType(command);
        stringFree(command);

        List left = listCreate();
        readSequenceToList(left, inputFile);
        List right = listCreate();
        readSequenceToList(right, inputFile);

        listReplace(sequence, left, right, comparator, listCopyCharElement);
        listPrint(sequence, listCharElementToString, NULL, stdout);

//        switch (commandType) {
//        case Delete:
//            printf("Delete ");
//            break;
//        case Insert:
//            printf("Insert ");
//            break;
//        case Replace:
//            printf("Replace ");
//            break;
//        case Unknown:
//            printf("Error: unknown command");
//            break;
//        }

        listFree(left);
        listFree(right);
    }

    listFree(sequence);
    fclose(inputFile);

    return 0;
}
