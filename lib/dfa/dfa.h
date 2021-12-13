#ifndef SPBU_C_HOMEWORKS_DFA_H
#define SPBU_C_HOMEWORKS_DFA_H

#include "stdbool.h"
#include <stdio.h>

typedef bool (*TransitionFunction)(char);
typedef struct Transition {
    int fromState;
    int toState;
    TransitionFunction transitionFunction;
} Transition;
Transition transitionCreate(int fromState, int toState, TransitionFunction transitionFunction);

typedef struct DFAError DFAError;
void dfaErrorFree(DFAError* dfaError);
void dfaErrorPrint(FILE* outputStream, DFAError* dfaError);

typedef struct DFA DFA;
DFA* dfaCreate(
    int transitionsCount, Transition* transitions, int acceptStateCount, int* acceptState, int startState);
void dfaFree(DFA* dfa);
DFAError* dfaIsStringInLanguage(DFA* dfa, const char* string);

#endif // SPBU_C_HOMEWORKS_DFA_H
