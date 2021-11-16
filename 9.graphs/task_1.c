#include "../lib/dataStructures/dict.h"
#include "../lib/graph/graph.h"
#include <stdio.h>

#define MAX_VERTEX_LENGTH 16

void readGraphEdges(Graph* g, int edgesCount, FILE* inputStream)
{
    char from[MAX_VERTEX_LENGTH] = "";
    char to[MAX_VERTEX_LENGTH] = "";
    int cost = 0;

    for (int i = 0; i < edgesCount; i++) {
        fscanf(inputStream, "%s %s %d", from, to, &cost);
        graphCreateEdge(g, stringDup(from), stringDup(to), cost);
    }
}

void calculateTheShortestPath(Graph* graph, String start, String end)
{
    List path = listCreate((void(*)(void*))stringFree);
    int pathLength = graphFindTheShortestPath(graph, start, end, path);
    printf("%d %d\n", listSize(path) - 1, pathLength);

    ListIterator pathIterator = listIteratorCreate(path);
    while (listIteratorHasMore(pathIterator)) {
        String vertex = listIteratorGetNext(pathIterator);
        stringPrint(vertex, stdout);
        printf(" ");
    }
    listIteratorFree(pathIterator);

    listFree(path);
}

int main()
{
    int vertexCount = 0;
    int edgesCount = 0;
    scanf("%d %d", &vertexCount, &edgesCount);

    Graph* graph = graphCreate();
    readGraphEdges(graph, edgesCount, stdin);

    char startBuffer[MAX_VERTEX_LENGTH] = "";
    char endBuffer[MAX_VERTEX_LENGTH] = "";
    scanf("%s %s", startBuffer, endBuffer);

    String start = stringDup(startBuffer);
    String end = stringDup(endBuffer);

    calculateTheShortestPath(graph, start, end);

    stringFree(end);
    stringFree(start);

    graphFree(graph);

    return 0;
}
