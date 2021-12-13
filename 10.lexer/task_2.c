#include "../lib/dfa/dfa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isE(char ch) { return ch == 'E'; }
bool isPlus(char ch) { return ch == '+'; }
bool isMinus(char ch) { return ch == '-'; }
bool isDigit(char ch) { return ch >= '0' && ch <= '9'; }
bool isDot(char ch) { return ch == '.'; }

// (+|-)?(\d*)(.?)(\d+)(E(+|-)?\d+)?
DFA* getNumbersDFA()
{
    int transitionsCount = 17;
    Transition* transitions = calloc(transitionsCount, sizeof(Transition));
    int tID = 0;
    transitions[tID++] = transitionCreate(0, 1, isPlus);
    transitions[tID++] = transitionCreate(0, 1, isMinus);
    transitions[tID++] = transitionCreate(0, 2, isDot);
    transitions[tID++] = transitionCreate(0, 3, isDigit);
    transitions[tID++] = transitionCreate(1, 3, isDigit);
    transitions[tID++] = transitionCreate(1, 2, isDot);
    transitions[tID++] = transitionCreate(2, 4, isDigit);
    transitions[tID++] = transitionCreate(3, 3, isDigit);
    transitions[tID++] = transitionCreate(3, 2, isDot);
    transitions[tID++] = transitionCreate(3, 5, isE);
    transitions[tID++] = transitionCreate(4, 4, isDigit);
    transitions[tID++] = transitionCreate(4, 5, isE);
    transitions[tID++] = transitionCreate(5, 6, isPlus);
    transitions[tID++] = transitionCreate(5, 6, isMinus);
    transitions[tID++] = transitionCreate(5, 7, isDigit);
    transitions[tID++] = transitionCreate(6, 7, isDigit);
    transitions[tID] = transitionCreate(7, 7, isDigit);

    int finiteStatesCount = 3;
    int* finiteStates = calloc(finiteStatesCount, sizeof(int));
    int fsID = 0;
    finiteStates[fsID++] = 4;
    finiteStates[fsID++] = 7;
    finiteStates[fsID] = 3;

    return dfaCreate(transitionsCount, transitions, finiteStatesCount, finiteStates, 0);
}

void pop(char* line, ssize_t lineLength)
{
    line[lineLength - 1] = '\0';
}

int main()
{
    DFA* numbersDFA = getNumbersDFA();

    char* inputLine = NULL;
    size_t inputBufferSize = 0;
    ssize_t inputLineLength = 0;

    while ((inputLineLength = getline(&inputLine, &inputBufferSize, stdin)) != -1) {
        pop(inputLine, inputLineLength);

        DFAError* error = dfaIsStringInLanguage(numbersDFA, inputLine);
        if (error) {
            printf("It's not a number :( ... Look at the error: ");
            dfaErrorPrint(stdout, error);
            dfaErrorFree(error);
        } else
            printf("This is a number! :)\n");
    }

    free(inputLine);
    dfaFree(numbersDFA);

    return 0;
}
