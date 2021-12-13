#include <stdlib.h>
#include <string.h>

#include "dfa.h"

typedef enum DFAErrorCode {
    TransitionNotFound,
    NotAcceptState
} DFAErrorCode;

struct DFAError {
    enum DFAErrorCode errorCode;
    char currentToken;
    int currentState;
};

static DFAError* dfaErrorCreate(DFAErrorCode errorCode, char currentToken, int currentState)
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
    case NotAcceptState:
        fprintf(outputStream, "there is not accept state: %d\n", dfaError->currentState);
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
    int acceptStatesCount;
    int* acceptStates;
    int startState;
};

DFA* dfaCreate(
    int transitionsCount,
    Transition* transitions,
    int acceptStatesCount,
    int* acceptStates,
    int startState)
{
    DFA* dfa = malloc(sizeof(DFA));

    dfa->transitionsCount = transitionsCount;
    dfa->transitions = transitions;
    dfa->acceptStatesCount = acceptStatesCount;
    dfa->acceptStates = acceptStates;
    dfa->startState = startState;

    return dfa;
}

void dfaFree(DFA* dfa)
{
    free(dfa->transitions);
    free(dfa->acceptStates);
    free(dfa);
}

static DFAError* isAcceptState(DFA* dfa, int state)
{
    for (int i = 0; i < dfa->acceptStatesCount; i++)
        if (state == dfa->acceptStates[i])
            return NULL;

    return dfaErrorCreate(NotAcceptState, ' ', state);
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

DFAError* dfaIsStringInLanguage(DFA* dfa, const char* string)
{
    int currentState = dfa->startState;

    while (*string != '\0') {
        DFAError* error = dfaMove(dfa, &currentState, *string);
        if (error)
            return error;

        string++;
    }

    return isAcceptState(dfa, currentState);
}
