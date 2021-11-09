#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/stack/stack.h"
#include "../lib/treemap/treemap.h"

#define SELECT_COMMAND_STRING "SELECT"
#define GET_COMMAND_STRING "GET"
#define ADD_COMMAND_STRING "ADD"

#define SELECT_COMMAND 1
#define GET_COMMAND 2
#define ADD_COMMAND 3
#define UNDEFINED_COMMAND 4

#define MAX_COMMAND_LENGTH 8
#define MAX_COMMAND_ARGS_LENGTH 2

void runSelectCommand(TreeMap* treeMap, int* args, FILE* outputFile)
{
    Value key = wrapInt(args[0]);
    Value resultKey = treeMapGetLowerBound(treeMap, key);

    if (isNone(resultKey)) {
//        fprintf(outputFile, "select %d ", key.intValue);

        fprintf(outputFile, "SORRY\n");

        return;
    }

    Value valueBefore = treeMapGet(treeMap, resultKey);
    Value newValue = wrapInt(getInt(valueBefore) - 1);
    treeMapDelete(treeMap, resultKey);
    if (getInt(newValue) > 0)
        treeMapInsert(treeMap, resultKey, newValue);

    print(resultKey, outputFile);

//    fprintf(outputFile, " (select %d: %d -> %d)", key.intValue, valueBefore.intValue, newValue.intValue);

    fprintf(outputFile, "\n");
}

void runGetCommand(TreeMap* treeMap, int* args, FILE* outputFile)
{
    Value result = treeMapGet(treeMap, wrapInt(args[0]));

    !isNone(result) ? print(result, outputFile) : fprintf(outputFile, "0");

//    fprintf(outputFile, " (get %d)", args[0]);

    fprintf(outputFile, "\n");
}

void runAddCommand(TreeMap* treeMap, int* args, FILE* outputFile)
{
    Value key = wrapInt(args[0]);
    Value value = wrapInt(args[1]);

    Value valueBefore = treeMapGet(treeMap, key);
    if (isNone(valueBefore)) {
        treeMapInsert(treeMap, key, value);
    } else {
        treeMapDelete(treeMap, key);
        treeMapInsert(treeMap, key, wrapInt(value.intValue + valueBefore.intValue));
    }

//    fprintf(outputFile, "add %d: %d -> %d\n", key.intValue, valueBefore.intValue, value.intValue + valueBefore.intValue);
}

typedef struct Command {
    int* args;
    void (*run)(TreeMap* treeMap, int* args, FILE* outputFile);
} Command;

Command* commandCreate(int* args)
{
    Command* command = malloc(sizeof(Command));

    command->args = args;

    return command;
}

void commandFree(Command* command)
{
    free(command->args);
    free(command);
}

size_t readCommandName(char* buffer, FILE* inputStream)
{
    fscanf(inputStream, "%s", buffer);

    if (!strcmp(buffer, SELECT_COMMAND_STRING))
        return SELECT_COMMAND;

    if (!strcmp(buffer, GET_COMMAND_STRING))
        return GET_COMMAND;

    if (!strcmp(buffer, ADD_COMMAND_STRING))
        return ADD_COMMAND;

    return UNDEFINED_COMMAND;
}

Command* getCommand(char* buffer, FILE* inputStream)
{
    size_t commandName = readCommandName(buffer, inputStream);
    int* args = calloc(MAX_COMMAND_ARGS_LENGTH, sizeof(int));

    Command* command = commandCreate(args);

    switch (commandName) {
    case SELECT_COMMAND:
        fscanf(inputStream, "%d", &args[0]);
        command->run = runSelectCommand;
        break;
    case GET_COMMAND:
        fscanf(inputStream, "%d", &args[0]);
        command->run = runGetCommand;
        break;
    case ADD_COMMAND:
        fscanf(inputStream, "%d", &args[0]);
        fscanf(inputStream, "%d", &args[1]);
        command->run = runAddCommand;
        break;
    }

    return command;
}

void processShopLogs(int operationsCount, FILE* inputFile, FILE* outputFile, FILE* outputFileLogs)
{
    TreeMap* products = treeMapCreate();
    char* readCommandBuffer = calloc(MAX_COMMAND_LENGTH, sizeof(char));

    for (int i = 0; i < 53; i++) {
        Command* command = getCommand(readCommandBuffer, inputFile);
        command->run(products, command->args, outputFile);
//        treeMapPrint(products, outputFile);
//        fprintf(outputFile," products\n");
        commandFree(command);
    }

    TreeMapIterator* productsIterator = treeMapIteratorCreate(products);
    while (treeMapIteratorHasElement(productsIterator)) {
        Node* product = treeMapIteratorGetNext(productsIterator);
        print(nodeGetKey(product), outputFileLogs);
        fprintf(outputFileLogs, " ");
        print(nodeGetValue(product), outputFileLogs);
        fprintf(outputFileLogs, "\n");
    }

    treeMapFree(products);
    free(readCommandBuffer);
    treeMapIteratorFree(productsIterator);
}

int main(int argc, char* argv[])
{

    if (argc != 4)
        printf("invalid count of arguments. please provide "
               "inputFile file path, outputFile and outputFileLogs file paths through space\n");

    char* inputFilePath = argv[1];
    char* outputFilePath = argv[2];
    char* outputFileLogsPath = argv[3];

    FILE* inputFile = fopen(inputFilePath, "r");
    if (!inputFile) {
        printf("invalid input file path: %s\n", inputFilePath);

        return 0;
    }

    FILE* outputFile = fopen(outputFilePath, "w");
    if (!outputFile) {
        printf("invalid output file path: %s\n", outputFilePath);

        return 0;
    }

    FILE* outputFileLogs = fopen(outputFileLogsPath, "w");
    if (!outputFileLogs) {
        printf("invalid output file logs path: %s\n", outputFileLogsPath);

        return 0;
    }

    int operationsCount = 0;
    fscanf(inputFile, "%d", &operationsCount);

    processShopLogs(operationsCount, inputFile, outputFile, outputFileLogs);

    fclose(inputFile);
    fclose(outputFile);
    fclose(outputFileLogs);

    return 0;
}
