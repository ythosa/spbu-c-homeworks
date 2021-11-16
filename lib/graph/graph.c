#include "graph.h"
#include "../dataStructures/dict.h"
#include "../dataStructures/list.h"
#include "../heap/heap.h"

struct Graph {
    Dict data;
};

Graph* graphCreate()
{
    Graph* g = malloc(sizeof(Graph));

    g->data = dictCreate((void(*)(void*))dictFree);

    return g;
}

void graphFree(Graph* g)
{
    dictFree(g->data);
    free(g);
}

void graphCreateEdge(Graph* g, String from, String to, int cost)
{
    Dict fromEdges = dictGet(g->data, from);
    if (!fromEdges) {
        fromEdges = dictCreate(free);
        dictPut(g->data, from, fromEdges);
    }

    int* pcost = malloc(sizeof(int));
    *pcost = cost;
    dictPut(fromEdges, to, pcost);
}

#define INF INT32_MAX

static Dict graphGetCosts(Graph* g, String start)
{
    Dict costs = dictCreate(free);

    DictIterator graphIterator = dictIteratorCreate(g->data);
    for (Element v = dictIteratorGetNext(graphIterator); v; v = dictIteratorGetNext(graphIterator)) {
        String vertex = elementGetKey(v);
        int* pcost = malloc(sizeof(int));
        *pcost = INF;
        dictPut(costs, stringCopy(vertex), pcost);
    }
    dictIteratorFree(graphIterator);

    int* startCost = dictGet(costs, start);
    *startCost = 0;

    return costs;
}

typedef struct VertexCost {
    String vertex;
    int cost;
} VertexCost;

VertexCost* vertexCostCreate(String vertex, int cost)
{
    VertexCost* vertexCost = malloc(sizeof(VertexCost));

    vertexCost->vertex = vertex;
    vertexCost->cost = cost;

    return vertexCost;
}

void vertexCostFree(VertexCost* v)
{
    stringFree(v->vertex);
    free(v);
}

int vertexCostsComparator(Value vertexCost1, Value vertexCost2)
{
    VertexCost* v1 = vertexCost1.pointerValue;
    VertexCost* v2 = vertexCost2.pointerValue;

    return v1->cost < v2->cost ? -1 : (v1->cost > v2->cost ? 1 : 0);
}

static void graphGetPath(Dict parents, String start, String end, List resultPath)
{
    String descendant = end;
    String parent = dictGet(parents, descendant);
    while (parent) {
        listUnshift(resultPath, stringCopy(descendant));
        descendant = parent;
        parent = dictGet(parents, parent);
    }
    listUnshift(resultPath, stringCopy(start));
}

int graphFindTheShortestPath(Graph* g, String start, String end, List resultPath)
{
    Dict costs = graphGetCosts(g, start);
    Dict used = dictCreate(free);
    Dict parents = dictCreate((void(*)(void*))stringFree);

    Heap* heap = heapCreate(vertexCostsComparator);
    heapInsert(heap, wrapPointer(vertexCostCreate(stringCopy(start), *(int*)dictGet(costs, start))));

    Value vertex = heapRemoveMin(heap);
    while (!isNone(vertex)) {
        VertexCost* vertexCost = getPointer(vertex);

        Dict neighbors = dictGet(g->data, vertexCost->vertex);
        if (!neighbors || dictGet(used, vertexCost->vertex)) {
            vertexCostFree(vertexCost);
            vertex = heapRemoveMin(heap);
            continue;
        }

        DictIterator neighboursIterator = dictIteratorCreate(neighbors);
        for (Element n = dictIteratorGetNext(neighboursIterator); n; n = dictIteratorGetNext(neighboursIterator)) {
            int* cost = elementGetValue(n);
            int newCost = vertexCost->cost + *cost;
            int* foundMinCost = dictGet(costs, elementGetKey(n));

            if (!foundMinCost) {
                foundMinCost = malloc(sizeof(int));
                *foundMinCost = newCost;
                dictPut(costs, stringCopy(elementGetKey(n)), foundMinCost);
                dictPut(parents, stringCopy(elementGetKey(n)), stringCopy(vertexCost->vertex));
            } else if (newCost < *foundMinCost) {
                dictDelete(parents, elementGetKey(n));
                dictPut(parents, stringCopy(elementGetKey(n)), stringCopy(vertexCost->vertex)); // update parent
                *foundMinCost = newCost; // update cost in {costs}
            }

            if (!dictGet(used, elementGetKey(n)))
                heapInsert(heap, wrapPointer(vertexCostCreate(stringCopy(elementGetKey(n)), newCost)));
        }
        dictIteratorFree(neighboursIterator);

        int* isUsed = malloc(sizeof(int));
        *isUsed = 1;

        dictPut(used, stringCopy(vertexCost->vertex), isUsed);
        vertexCostFree(vertexCost);
        vertex = heapRemoveMin(heap);
    }

    int result = *(int*)dictGet(costs, end);
    graphGetPath(parents, start, end, resultPath);

    heapFree(heap);
    dictFree(parents);
    dictFree(used);
    dictFree(costs);

    return result;
}
