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

void readVector(Vector* vector, FILE* inputStream)
{
    char* line = NULL;
    size_t lineSize = 0;
    ssize_t lineLength = getline(&line, &lineSize, inputStream);
    for (int i = 0; i < lineLength; i += 2) {
        vectorPushback(vector, line[i] - '0');
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        printf("invalid count of arguments. please provide inputFile and outputFile file paths");

        return 0;
    }

    printf("Input a: ");
    int a = 0;
    scanf("%d", &a);

    printf("Input b: ");
    int b = 0;
    scanf("%d", &b);

    if (a > b) {
        swap(a, b);
    }

    Vector* numsLowerThenA = vectorCreate();
    Vector* numsInABInterval = vectorCreate();
    Vector* numsGreaterThenB = vectorCreate();

    FILE* inputFile = fopen(argv[1], "r");
    char* line = NULL;
    size_t lineSize = 0;
    ssize_t lineLength = getline(&line, &lineSize, inputFile);
    for (int i = 0; i < lineLength; i += 2) {
        int currentNumber = line[i] - '0';
        if (currentNumber < a) {
            vectorPushback(numsLowerThenA, currentNumber);
        } else if (currentNumber > b) {
            vectorPushback(numsGreaterThenB, currentNumber);
        } else {
            vectorPushback(numsInABInterval, currentNumber);
        }
    }
    fclose(inputFile);

    FILE* outputFile = fopen(argv[2], "w");
    vectorPrint(numsLowerThenA, outputFile);
    vectorPrint(numsInABInterval, outputFile);
    vectorPrint(numsGreaterThenB, outputFile);
    fclose(outputFile);
}
