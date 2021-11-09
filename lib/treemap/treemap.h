#include "../values/values.h"

typedef struct TreeMap TreeMap;

TreeMap* treeMapCreate();
void treeMapFree(TreeMap* treeMap);
void treeMapPrint(TreeMap* treeMap, FILE* destination);
void treeMapInsert(TreeMap* treeMap, Value key, Value value);
void treeMapDelete(TreeMap* treeMap, Value key);
Value treeMapGet(TreeMap* treeMap, Value key);
bool treeMapHasKey(TreeMap* treeMap, Value key);
Value treeMapGetMaximum(TreeMap* treeMap);
Value treeMapGetMinimum(TreeMap* treeMap);
Value treeMapGetUpperBound(TreeMap* treeMap, Value key);
Value treeMapGetLowerBound(TreeMap* treeMap, Value key);
