#include "../lib/dataStructures/list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    int** incidenceMatrix;
    int vertexCount;
    int edgesCount;
} Graph;

Graph* graphCreate(int** incidenceMatrix, int vertexCount, int edgesCount)
{
    Graph* graph = malloc(sizeof(Graph));

    graph->incidenceMatrix = incidenceMatrix;
    graph->vertexCount = vertexCount;
    graph->edgesCount = edgesCount;

    return graph;
}

void graphFree(Graph* graph)
{
    for (int i = 0; i < graph->vertexCount; i++)
        free(graph->incidenceMatrix[i]);
    free(graph->incidenceMatrix);
    free(graph);
}

int** transposeIncidenceMatrix(int** matrix, int vertexCount, int edgesCount)
{
    int** transposed = calloc(vertexCount, sizeof(int*));
    for (int i = 0; i < vertexCount; i++) {
        transposed[i] = calloc(edgesCount, sizeof(int));
        for (int j = 0; j < edgesCount; j++)
            transposed[i][j] = -matrix[i][j];
    }

    return transposed;
}

Graph* graphTransposed(Graph* graph)
{
    Graph* transposed = graphCreate(
        transposeIncidenceMatrix(graph->incidenceMatrix, graph->vertexCount, graph->edgesCount),
        graph->vertexCount,
        graph->edgesCount);

    return transposed;
}

void graphDFS(Graph* graph, int vertex, bool* visited)
{
    visited[vertex] = true;

    for (int edgeNumber = 0; edgeNumber < graph->edgesCount; edgeNumber++)
        if (graph->incidenceMatrix[vertex][edgeNumber] == 1)
            for (int vertexNumber = 0; vertexNumber < graph->vertexCount; vertexNumber++)
                if (graph->incidenceMatrix[vertexNumber][edgeNumber] == -1 && !visited[vertexNumber])
                    graphDFS(graph, vertexNumber, visited);
}

List graphFindAllMotherVertices(Graph* graph)
{
    bool* visited = calloc(graph->vertexCount, sizeof(bool));

    int motherVertex = 0;
    for (int i = 0; i < graph->vertexCount; i++) {
        if (visited[i] == false) {
            graphDFS(graph, i, visited);
            motherVertex = i;
        }
    }

    free(visited);
    visited = calloc(graph->vertexCount, sizeof(bool));
    graphDFS(graph, motherVertex, visited);
    for (int i = 0; i < graph->vertexCount; i++) {
        if (!visited[i]) {
            return NULL;
        }
    }

    Graph* transposedGraph = graphTransposed(graph);
    free(visited);
    visited = calloc(graph->vertexCount, sizeof(bool));
    graphDFS(transposedGraph, motherVertex, visited);

    List motherVertexes = listCreate(free);

    for (int i = 0; i < graph->vertexCount; i++)
        if (visited[i]) {
            int* vertexPointer = malloc(sizeof(int));
            *vertexPointer = i;
            listPushback(motherVertexes, vertexPointer);
        }

    free(visited);
    graphFree(transposedGraph);

    return motherVertexes;
}

int** getMatrixFromInput(int rowsCount, int colsCount)
{
    int** matrix = malloc(rowsCount * sizeof(int*));

    for (int i = 0; i < rowsCount; i++) {
        matrix[i] = malloc(colsCount * sizeof(int));
        for (int j = 0; j < colsCount; j++)
            scanf("%d", &matrix[i][j]);
    }

    return matrix;
}

int main()
{
    printf("Input vertex and edges cound: ");
    int vertexCount = 0;
    int edgesCount = 0;
    scanf("%d %d", &vertexCount, &edgesCount);

    Graph* graph = graphCreate(getMatrixFromInput(vertexCount, edgesCount), vertexCount, edgesCount);

    List motherVertexes = graphFindAllMotherVertices(graph);
    printf("Found mother vertexes: ");
    if (!motherVertexes)
        return 0;

    ListIterator motherVertexesIterator = listIteratorCreate(motherVertexes);
    while (listIteratorHasMore(motherVertexesIterator))
        printf("%d", *(int*)listIteratorGetNext(motherVertexesIterator));
    listIteratorFree(motherVertexesIterator);

    listFree(motherVertexes);

    graphFree(graph);

    return 0;
}
