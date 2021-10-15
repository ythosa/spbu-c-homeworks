#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../lib/dataStructures/list.h"

#define DELETE_COMMAND "DELETE"
#define INSERT_COMMAND "INSERT"
#define REPLACE_COMMAND "REPLACE"

#define MAX_COMMAND_LENGTH 8
#define MAX_SEQUENCE_LENGTH 128

String charPointerToString(const char* c)
{
    return stringPush(stringDup(""), *c);
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

void readSeqToList(List sequence, char* buffer, FILE* inputStream)
{
    fscanf(inputStream, "%s", buffer);

    for (char* pointer = buffer; *pointer; pointer++) {
        char* symbol = malloc(sizeof(char));
        *symbol = *pointer;
        listPushback(sequence, symbol);
    }
}

String readCommand(FILE* inputStream)
{
    char buffer[MAX_COMMAND_LENGTH] = "";
    fscanf(inputStream, "%s", buffer);

    return stringDup(buffer);
}

typedef struct Command {
    String name;
    bool (*run)(List, List, List);
} Command;

Command* commandCreate(String name, bool (*run)(List, List, List))
{
    Command* command = malloc(sizeof(Command));

    command->name = name;
    command->run = run;

    return command;
}

void commandFree(Command* command)
{
    stringFree(command->name);
    free(command);
}

bool runDeleteCommand(List sequence, List leftOperand, List rightOperand)
{
    return listDeleteFromSequenceBySequence(sequence, leftOperand, rightOperand,
        (bool(*)(void*, void*))charPointersComparator);
}

bool runInsertCommand(List sequence, List leftOperand, List rightOperand)
{
    return listInsertSequenceAfterSequence(sequence, leftOperand, rightOperand,
        (bool(*)(void*, void*))charPointersComparator, (void* (*)(void*))charPointerCopy);
}

bool runReplaceCommand(List sequence, List leftOperand, List rightOperand)
{
    return listReplaceSequence(sequence, leftOperand, rightOperand,
        (bool(*)(void*, void*))charPointersComparator, (void* (*)(void*))charPointerCopy);
}

List getCommands()
{
    Command* delete = commandCreate(stringDup(DELETE_COMMAND), runDeleteCommand);
    Command* insert = commandCreate(stringDup(INSERT_COMMAND), runInsertCommand);
    Command* replace = commandCreate(stringDup(REPLACE_COMMAND), runReplaceCommand);

    List commands = listCreate((void(*)(void*))commandFree);

    listPushback(commands, delete);
    listPushback(commands, insert);
    listPushback(commands, replace);

    return commands;
}

void handleRunCommandError(String commandName, List sequence, List leftOperand, List rightOperand)
{
    printf("failed to ");
    stringPrint(commandName, stdout);
    printf("in: ");
    listPrint(sequence, (String(*)(void*))charPointerToString, NULL, stdout);
    printf(" left operand: ");
    listPrint(leftOperand, (String(*)(void*))charPointerToString, NULL, stdout);
    printf(" right operand: ");
    listPrint(rightOperand, (String(*)(void*))charPointerToString, NULL, stdout);
    printf("\n");
}

void recoverDNA(List sequence, int operationsLength, FILE* inputFile, FILE* outputFile)
{
    char* readSequenceBuffer = calloc(sizeof(char), MAX_SEQUENCE_LENGTH);
    List commands = getCommands();
    for (int i = 0; i < operationsLength; i++) {
        String userCommand = readCommand(inputFile);
        List leftOperand = listCreate(free);
        readSeqToList(leftOperand, readSequenceBuffer, inputFile);
        List rightOperand = listCreate(free);
        readSeqToList(rightOperand, readSequenceBuffer, inputFile);

        ListIterator commandsIterator = listIteratorCreate(commands);
        while (listIteratorHasMore(commandsIterator)) {
            Command* command = listIteratorGetNext(commandsIterator);
            if (!stringCmp(userCommand, command->name)) {
                if (!command->run(sequence, leftOperand, rightOperand)) {
                    handleRunCommandError(command->name, sequence, leftOperand, rightOperand);

                    listIteratorFree(commandsIterator);

                    stringFree(userCommand);
                    listFree(leftOperand);
                    listFree(rightOperand);

                    free(readSequenceBuffer);
                    listFree(commands);

                    return;
                }
            }
        }
        listIteratorFree(commandsIterator);

        stringFree(userCommand);
        listFree(leftOperand);
        listFree(rightOperand);

        listPrint(sequence, (String(*)(void*))charPointerToString, NULL, outputFile);
        fprintf(outputFile, "\n");
    }

    listFree(commands);
    free(readSequenceBuffer);
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

    char* sequenceBuffer = calloc(sizeof(char), sequenceLength);
    List sequence = listCreate(free);
    readSeqToList(sequence, sequenceBuffer, inputFile);
    free(sequenceBuffer);

    int operationsLength = 0;
    fscanf(inputFile, "%d", &operationsLength);

    recoverDNA(sequence, operationsLength, inputFile, outputFile);

    listFree(sequence);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
