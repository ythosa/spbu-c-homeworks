#include "../values/values.h"

typedef struct Stack Stack;

Stack* stackCreate();
void stackFree(Stack* stack);
void stackShallowFree(Stack* stack);
void stackPush(Stack* stack, Value data);
Value stackPop(Stack* stack);
int stackGetSize(Stack* stack);
bool isEmpty(Stack* stack);
