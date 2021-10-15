#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

enum CommandStatusCode {
    Success,
    DeleteError,
    InsertError,
    ReplaceError,
    UnknownCommandTypeError
};

String charPointerToString(const char* c)
{
    return stringPush(stringDup(""), *c);
}

char charPointerToChar(const char* c)
{
    return *c;
}

bool charPointersComparator(const char* c1, const char* c2)
{
    return *c1 == *c2;
}

char* charPointerCopy(const char* c)
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

String readCommand(FILE* inputStream)
{
    List command = listCreate(free);
    readSeqToList(command, inputStream);
    String result = listToString(command, charPointerToChar);
    listFree(command);

    return result;
}

size_t identifyCommand(String command)
{
    size_t commandType = Unknown;

    String deleteCommand = stringDup(DELETE_COMMAND);
    String insertCommand = stringDup(INSERT_COMMAND);
    String replaceCommand = stringDup(REPLACE_COMMAND);

    if (stringCmp(command, deleteCommand) == 0)
        commandType = Delete;
    else if (stringCmp(command, insertCommand) == 0)
        commandType = Insert;
    else if (stringCmp(command, replaceCommand) == 0)
        commandType = Replace;

    stringFree(deleteCommand);
    stringFree(insertCommand);
    stringFree(replaceCommand);

    return commandType;
}

size_t applyCommandToSequence(List sequence, size_t commandType, List leftOperand, List rightOperand)
{
    switch (commandType) {
    case Delete:
        if (!listDeleteFromSequenceBySequence(
                sequence, leftOperand, rightOperand, charPointersComparator))
            return DeleteError;
        break;
    case Insert:
        if (!listInsertSequenceAfterSequence(
                sequence, leftOperand, rightOperand, charPointersComparator, charPointerCopy))
            return InsertError;
        break;
    case Replace:
        if (!listReplaceSequence(
                sequence, leftOperand, rightOperand, charPointersComparator, charPointerCopy))
            return ReplaceError;
        break;
    case Unknown:
        return UnknownCommandTypeError;
    }

    return Success;
}

void handleError(size_t errorCode, List sequence, List leftOperand, List rightOperand)
{
    if (errorCode == UnknownCommandTypeError) {
        printf("Unknown command\n");
    }

    switch (errorCode) {
    case DeleteError:
        printf("Failed to delete in: ");
        break;
    case InsertError:
        printf("Failed to insert in: ");
        break;
    case ReplaceError:
        printf("Failed to replace in: ");
        break;
    }

    listPrint(sequence, charPointerToString, NULL, stdout);
    printf(" left operand: ");
    listPrint(leftOperand, charPointerToString, NULL, stdout);
    printf(" right operand: ");
    listPrint(rightOperand, charPointerToString, NULL, stdout);
    printf("\n");
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("invalid count of arguments. please provide "
               "inputFile file path and outputFile file path through space\n");

        return 0;
    }

    char* inputFilePath = argv[1];
    FILE* inputFile = fopen(inputFilePath, "r");
    if (!inputFile) {
        printf("invalid input file path: %s\n", inputFilePath);

        return 0;
    }

    char* outputFilePath = argv[2];
    FILE* outputFile = fopen(outputFilePath, "w");

    int sequenceLength = 0;
    fscanf(inputFile, "%d", &sequenceLength);

    List sequence = listCreate(free);
    readSeqToList(sequence, inputFile);

    int operationsLength = 0;
    fscanf(inputFile, "%d", &operationsLength);

    for (int i = 0; i < operationsLength; i++) {
        String command = readCommand(inputFile);
        size_t commandType = identifyCommand(command);
        stringFree(command);

        List leftOperand = listCreate(free);
        readSeqToList(leftOperand, inputFile);
        List rightOperand = listCreate(free);
        readSeqToList(rightOperand, inputFile);

        size_t statusCode = applyCommandToSequence(sequence, commandType, leftOperand, rightOperand);
        if (statusCode != Success) {
            handleError(statusCode, sequence, leftOperand, rightOperand);

            listFree(leftOperand);
            listFree(rightOperand);
            listFree(sequence);
            fclose(inputFile);
            fclose(outputFile);

            exit(0);
        }

        listPrint(sequence, (String(*)(void*))charPointerToString, NULL, outputFile);
        fprintf(outputFile, "\n");

        listFree(leftOperand);
        listFree(rightOperand);
    }

    listFree(sequence);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
