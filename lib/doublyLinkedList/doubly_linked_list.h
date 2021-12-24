#ifndef SPBU_C_HOMEWORKS_DOUBLYLINKEDLIST_H
#define SPBU_C_HOMEWORKS_DOUBLYLINKEDLIST_H

#include "stdbool.h"

typedef struct List* List;
List listCreate();
void listFree(List list);
void listPushback(List list, int data);
bool listIsSymmetric(List list);

#endif // SPBU_C_HOMEWORKS_DOUBLYLINKEDLIST_H
