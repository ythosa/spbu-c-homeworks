#ifndef SPBU_C_HOMEWORKS_VECTOR_H
#define SPBU_C_HOMEWORKS_VECTOR_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Vector Vector;

Vector* vectorCreate();
void vectorFree(Vector* vector);
int vectorSize(Vector* vector);
void vectorPushback(Vector* vector, int data);
void vectorPrint(Vector* vector, FILE* destination);
double vectorLength(Vector* vector);
Vector* vectorPlus(Vector* leftOperand, Vector* rightOperand);
Vector* vectorMinus(Vector* leftOperand, Vector* rightOperand);
bool vectorDotProduct(int* result, Vector* leftOperand, Vector* rightOperand);

#endif // SPBU_C_HOMEWORKS_VECTOR_H
