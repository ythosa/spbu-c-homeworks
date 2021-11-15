#ifndef SPBU_C_HOMEWORKS_TREEMAP_H
#define SPBU_C_HOMEWORKS_TREEMAP_H

#include "../list/list.h"
#include "../values/values.h"

typedef struct Node Node;
Value nodeGetKey(Node*);
Value nodeGetValue(Node*);

typedef struct TreeMap TreeMap;
TreeMap* treeMapCreate(Comparator);
void treeMapFree(TreeMap* treeMap);
void treeMapPrint(TreeMap* treeMap, FILE* destination);
void treeMapPut(TreeMap* treeMap, Value key, Value value);
void treeMapDelete(TreeMap* treeMap, Value key);
Value treeMapGet(TreeMap* treeMap, Value key);
bool treeMapHasKey(TreeMap* treeMap, Value key);
Value treeMapGetMaximum(TreeMap* treeMap);
Value treeMapGetMinimum(TreeMap* treeMap);
Value treeMapGetUpperBound(TreeMap* treeMap, Value key);
Value treeMapGetLowerBound(TreeMap* treeMap, Value key);
void treeMapJoin(TreeMap* map, TreeMap* another);
TreeMap* treeMapSplit(TreeMap* map, Value splitKey);
void treeMapRemoveKeys(TreeMap* treeMap, Value left, Value right);
List treeMapGetAll(TreeMap* treeMap, Value left, Value right);

typedef struct TreeMapIterator TreeMapIterator;
TreeMapIterator* treeMapIteratorCreate(TreeMap* treeMap);
void treeMapIteratorFree(TreeMapIterator* treeMapIterator);
bool treeMapIteratorHasElement(TreeMapIterator* treeMapIterator);
Node* treeMapIteratorGetNext(TreeMapIterator* treeMapIterator);

#endif // SPBU_C_HOMEWORKS_TREEMAP_H
