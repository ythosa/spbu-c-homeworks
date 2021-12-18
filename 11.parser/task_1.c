#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/dataStructures/dict.h"
#include "../lib/dataStructures/list.h"
#include "../lib/slice.h"
#include "../lib/stack.h"

typedef struct Rule {
    char* nonTerminal;
    int symbolsCount;
    char** symbols;
} Rule;

Rule* ruleCreate(char* nonTerminal, int symbolsCount, char** symbols)
{
    Rule* rule = malloc(sizeof(Rule));

    rule->nonTerminal = nonTerminal;
    rule->symbolsCount = symbolsCount;
    rule->symbols = symbols;

    return rule;
}

void ruleFree(Rule* rule)
{
    free(rule->nonTerminal);
    for (int i = 0; i < rule->symbolsCount; i++)
        free(rule->symbols[i]);
    free(rule->symbols);
    free(rule);
}

Rule* getRuleFromString(char* string)
{
    char* token = strtok(string, " ");

    char* nonTerminal = calloc(strlen(token) + 1, sizeof(char));
    strcpy(nonTerminal, token);
    token = strtok(NULL, " ");

    int symbolsCount = atoi(token);
    token = strtok(NULL, " ");

    char** symbols = calloc(symbolsCount, sizeof(char*));
    for (int i = 0; i < symbolsCount; i++) {
        char* symbol = calloc(strlen(token) + 1, sizeof(char));
        strcpy(symbol, token);
        symbols[i] = symbol;
        token = strtok(NULL, " ");
    }

    return ruleCreate(nonTerminal, symbolsCount, symbols);
}

typedef struct Grammar {
    List nonTerminals;
    Dict rules;
} Grammar;

Grammar* grammarCreate()
{
    Grammar* grammar = malloc(sizeof(Grammar));

    grammar->nonTerminals = listCreate(free);
    grammar->rules = dictCreate(listFree);

    return grammar;
}

void grammarFree(Grammar* grammar)
{
    dictFree(grammar->rules);
    listFree(grammar->nonTerminals);
    free(grammar);
}

void addRule(Dict rules, char* nonTerminal, Rule* rule)
{
    String nonTerminal_s = stringDup(nonTerminal);

    List rulesForNonTerminals = dictGet(rules, nonTerminal_s);
    if (rulesForNonTerminals) {
        listPushback(rulesForNonTerminals, rule);
        stringFree(nonTerminal_s);

        return;
    }

    rulesForNonTerminals = listCreate(ruleFree);
    listPushback(rulesForNonTerminals, rule);
    dictPut(rules, nonTerminal_s, rulesForNonTerminals);
}

Grammar* readGrammar(FILE* inputStream)
{
    Grammar* grammar = grammarCreate();

    char* line = NULL;
    size_t lineLength = 0;

    while ((getline(&line, &lineLength, inputStream)) != -1) {
        Rule* rule = getRuleFromString(line);
        char* nonTerminal = calloc(strlen(rule->nonTerminal) + 1, sizeof(char));
        strcpy(nonTerminal, rule->nonTerminal);

        listPushback(grammar->nonTerminals, nonTerminal);
        addRule(grammar->rules, nonTerminal, rule);
    }

    return grammar;
}

Slice* tokenizeInputString(char* string)
{
    Slice* tokens = sliceCreate(sizeof(char*), free);
    char* token = strtok(string, " ");
    while (token) {
        puts(token);
        sliceAdd(tokens, token);
        token = strtok(NULL, " ");
    }

    return tokens;
}

int main()
{

    return 0;
}
