#ifndef SPBU_C_HOMEWORKS_STACK_H
#define SPBU_C_HOMEWORKS_STACK_H

typedef void (*Destructor)(void*);

typedef struct Stack Stack;
Stack* stackCreate(Destructor dataDestructor);
void stackFree(Stack*);
void stackPush(Stack* stack, void* data);
void* stackPop(Stack* stack);

#endif // SPBU_C_HOMEWORKS_STACK_H
