#ifndef SPBU_C_HOMEWORKS_GRAPH_H
#define SPBU_C_HOMEWORKS_GRAPH_H

#include "../dataStructures/list.h"
#include "../dataStructures/string.h"
#include "../values/values.h"

typedef struct Graph Graph;

Graph* graphCreate();
void graphFree(Graph*);

void graphCreateEdge(Graph* g, String from, String to, int cost);
int graphFindTheShortestPath(Graph* g, String start, String end, List resultPath);

#endif // SPBU_C_HOMEWORKS_GRAPH_H
