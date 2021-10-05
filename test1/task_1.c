#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

typedef struct Vector {
    int size;
    Node* head;
    Node* tail;
} Vector;

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

void vectorPrint(Vector* list, FILE* destination)
{
    Node* currentNode = list->head;
    while (currentNode) {
        fprintf(destination, "%d ", currentNode->data);
        currentNode = currentNode->next;
    }
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

void readVector(Vector* vector, FILE* inputStream)
{
    char* line = NULL;
    size_t lineSize = 0;
    ssize_t lineLength = getline(&line, &lineSize, inputStream);
    for (int i = 0; i < lineLength; i += 2) {
        vectorPushback(vector, line[i] - '0');
    }
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("invalid count of arguments. please provide inputFile file path");

        return 0;
    }

    FILE* inputFile = fopen(argv[1], "r");

    Vector* vector1 = vectorCreate();
    readVector(vector1, inputFile);

    Vector* vector2 = vectorCreate();
    readVector(vector2, inputFile);

    Vector* vectorSum = vectorPlus(vector1, vector2);
    printf("Vectors sum: ");
    vectorPrint(vectorSum, stdout);
    vectorFree(vectorSum);
    printf("\n");

    Vector* vectorDiff = vectorMinus(vector1, vector2);
    printf("Vectors minus: ");
    vectorPrint(vectorDiff, stdout);
    vectorFree(vectorDiff);
    printf("\n");

    int dotProduct = 0;
    if (!vectorDotProduct(&dotProduct, vector1, vector2)) {
        printf("Error counting dot product\n");
    }
    printf("Vectors dot product: %d\n", dotProduct);

    vectorFree(vector1);
    vectorFree(vector2);

    return 0;
}
