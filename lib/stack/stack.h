#ifndef SPBU_C_HOMEWORKS_STACK_H
#define SPBU_C_HOMEWORKS_STACK_H

#include "../values/values.h"

typedef struct Stack Stack;

Stack* stackCreate();
void stackFree(Stack* stack);
void stackShallowFree(Stack* stack);
void stackPush(Stack* stack, Value data);
Value stackPop(Stack* stack);
int stackGetSize(Stack* stack);
bool stackIsEmpty(Stack* stack);

#endif // SPBU_C_HOMEWORKS_STACK_H
