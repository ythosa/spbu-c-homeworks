#include <stdlib.h>
#include <string.h>

#include "dfa.h"

typedef enum DFAErrorCode {
    TransitionNotFound,
    NotFiniteState
} DFAErrorCode;

struct DFAError {
    enum DFAErrorCode errorCode;
    char currentToken;
    int currentState;
};

DFAError* dfaErrorCreate(DFAErrorCode errorCode, char currentToken, int currentState)
{
    DFAError* dfaError = malloc(sizeof(DFAError));

    dfaError->errorCode = errorCode;
    dfaError->currentToken = currentToken;
    dfaError->currentState = currentState;

    return dfaError;
}

void dfaErrorFree(DFAError* dfaError)
{
    free(dfaError);
}

void dfaErrorPrint(FILE* outputStream, DFAError* dfaError)
{
    switch (dfaError->errorCode) {
    case TransitionNotFound:
        fprintf(outputStream, "there is no transition for token \"%c\" (state %d)\n",
            dfaError->currentToken, dfaError->currentState);
        break;
    case NotFiniteState:
        fprintf(outputStream, "there is not finite state: %d\n", dfaError->currentState);
        break;
    default:
        fprintf(outputStream, "there is error in token \"%c\" (state %d)\n",
            dfaError->currentToken, dfaError->currentState);
        break;
    }
}

Transition transitionCreate(int fromState, int toState, TransitionFunction transitionFunction)
{
    Transition transition = { fromState, toState, transitionFunction };

    return transition;
}

struct DFA {
    int transitionsCount;
    Transition* transitions;
    int finiteStatesCount;
    int* finiteStates;
    int startState;
};

DFA* dfaCreate(
    int transitionsCount,
    Transition* transitions,
    int finiteStatesCount,
    int* finiteStates,
    int startState)
{
    DFA* dfa = malloc(sizeof(DFA));

    dfa->transitionsCount = transitionsCount;
    dfa->transitions = transitions;
    dfa->finiteStatesCount = finiteStatesCount;
    dfa->finiteStates = finiteStates;
    dfa->startState = startState;

    return dfa;
}

void dfaFree(DFA* dfa)
{
    free(dfa->transitions);
    free(dfa->finiteStates);
    free(dfa);
}

static DFAError* isFiniteState(DFA* dfa, int state)
{
    bool isFiniteState = false;

    for (int i = 0; i < dfa->finiteStatesCount; i++)
        if (state == dfa->finiteStates[i]) {
            isFiniteState = true;
            break;
        }

    return isFiniteState ? NULL : dfaErrorCreate(NotFiniteState, ' ', state);
}

static DFAError* dfaMove(DFA* dfa, int* state, char token)
{
    for (int i = 0; i < dfa->transitionsCount; i++) {
        Transition transition = dfa->transitions[i];
        if (transition.fromState == *state && transition.transitionFunction(token)) {
            *state = transition.toState;

            return NULL;
        }
    }

    return dfaErrorCreate(TransitionNotFound, token, *state);
}

DFAError* dfaIsStringInAlphabet(DFA* dfa, const char* string)
{
    int currentState = dfa->startState;

    while (*string != '\0') {
        DFAError* error = dfaMove(dfa, &currentState, *string);
        if (error)
            return error;

        string++;
    }

    return isFiniteState(dfa, currentState);
}
