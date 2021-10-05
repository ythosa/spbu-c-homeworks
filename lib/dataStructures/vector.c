#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

typedef struct Node {
    struct Node* next;
    int data;
} Node;

Node* nodeCreate(Node* next, int data)
{
    Node* node = malloc(sizeof(Node));

    node->next = next;
    node->data = data;

    return node;
}

void nodeFree(Node* node)
{
    free(node);
}

struct Vector {
    int size;
    Node* head;
    Node* tail;
};

Vector* vectorCreate()
{
    Vector* vector = malloc(sizeof(Vector));

    vector->size = 0;
    vector->head = NULL;
    vector->tail = NULL;

    return vector;
}

void vectorFree(Vector* vector)
{
    Node* next = NULL;
    for (Node* node = vector->head; node; node = next) {
        next = node->next;
        nodeFree(node);
    }

    free(vector);
}

int vectorSize(Vector* vector)
{
    return vector->size;
}

void vectorPushback(Vector* vector, int data)
{
    vector->size++;

    if (!vector->head) {
        vector->tail = NULL;
        vector->head = nodeCreate(vector->tail, data);

        return;
    }

    Node* newNode = nodeCreate(NULL, data);

    if (!vector->tail) {
        vector->tail = newNode;
        vector->head->next = vector->tail;

        return;
    }

    vector->tail->next = newNode;
    vector->tail = newNode;
}

void vectorPrint(Vector* vector, FILE* destination)
{
    Node* currentNode = vector->head;
    while (currentNode) {
        fprintf(destination, "%d ", currentNode->data);
        currentNode = currentNode->next;
    }
}

double vectorLength(Vector* vector)
{
    int squaresSum = 0;

    Node* currentNode = vector->head;
    while (currentNode) {
        squaresSum += currentNode->data * currentNode->data;
        currentNode = currentNode->next;
    }

    return sqrt(squaresSum);
}

Vector* vectorPlus(Vector* leftOperand, Vector* rightOperand)
{
    if (leftOperand->size != rightOperand->size)
        return NULL;

    Vector* result = vectorCreate();
    Node* currentLeftOperandNode = leftOperand->head;
    Node* currentRightOperandNode = rightOperand->head;
    for (int i = 0; i < leftOperand->size; i++) {
        vectorPushback(result, currentLeftOperandNode->data + currentRightOperandNode->data);
        currentRightOperandNode = currentLeftOperandNode->next;
        currentRightOperandNode = currentRightOperandNode->next;
    }

    return result;
}

Vector* vectorMinus(Vector* leftOperand, Vector* rightOperand)
{
    if (leftOperand->size != rightOperand->size)
        return NULL;

    Vector* result = vectorCreate();

    Node* currentLeftOperandNode = leftOperand->head;
    Node* currentRightOperandNode = rightOperand->head;
    for (int i = 0; i < leftOperand->size; i++) {
        vectorPushback(result, currentLeftOperandNode->data - currentRightOperandNode->data);
        currentLeftOperandNode = currentLeftOperandNode->next;
        currentRightOperandNode = currentRightOperandNode->next;
    }

    return result;
}

bool vectorDotProduct(int* result, Vector* leftOperand, Vector* rightOperand)
{
    if (leftOperand->size != rightOperand->size)
        return false;

    Node* currentLeftOperandNode = leftOperand->head;
    Node* currentRightOperandNode = rightOperand->head;
    for (int i = 0; i < leftOperand->size; i++) {
        *result += currentLeftOperandNode->data * currentRightOperandNode->data;
        currentLeftOperandNode = currentLeftOperandNode->next;
        currentRightOperandNode = currentRightOperandNode->next;
    }

    return true;
}
