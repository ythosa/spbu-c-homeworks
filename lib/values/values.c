#include "values.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void assertCommonType(Value first, Value second)
{
    assert(first.type == second.type);
}

void assertType(Value value, ValueType type)
{
    assert(value.type == type);
}

Value wrapInt(int value)
{
    return (Value) { .type = INT_TYPE, .intValue = value };
}

Value wrapDouble(double value)
{
    return (Value) { .type = DOUBLE_TYPE, .doubleValue = value };
}

Value wrapString(char* value)
{
    return (Value) { .type = STRING_TYPE, .stringValue = value };
}

Value wrapPointer(void* value)
{
    return (Value) { .type = POINTER_TYPE, .pointerValue = value };
}

Value wrapNone()
{
    return (Value) { .type = NONE_TYPE };
}

int getInt(Value value)
{
    assertType(value, INT_TYPE);
    return value.intValue;
}

double getDouble(Value value)
{
    assertType(value, DOUBLE_TYPE);
    return value.doubleValue;
}

char* getString(Value value)
{
    assertType(value, STRING_TYPE);
    return value.stringValue;
}

void* getPointer(Value value)
{
    assertType(value, POINTER_TYPE);
    return value.pointerValue;
}

bool isNone(Value value)
{
    return value.type == NONE_TYPE;
}

static int compareInt(int first, int second)
{
    return first < second ? -1 : (first > second ? 1 : 0);
}

static int compareDouble(double first, double second)
{
    return first < second ? -1 : (first > second ? 1 : 0);
}

static int compareString(char* first, char* second)
{
    int compareResult = strcmp(first, second);

    return compareResult > 0 ? 1 : compareResult < 0 ? -1
                                                     : 0;
}

static int comparePointer(void* firstPointer, void* secondPointer)
{
    uintptr_t first = (uintptr_t)firstPointer;
    uintptr_t second = (uintptr_t)secondPointer;
    return first < second ? -1 : (first > second ? 1 : 0);
}

bool equals(Value first, Value second)
{
    return compare(first, second) == 0;
}

int compare(Value first, Value second)
{
    if (first.type != second.type)
        return first.type - second.type;
    switch (first.type) {
    case INT_TYPE:
        return compareInt(first.intValue, second.intValue);
    case DOUBLE_TYPE:
        return compareDouble(first.doubleValue, second.doubleValue);
    case STRING_TYPE:
        return compareString(first.stringValue, second.stringValue);
    case POINTER_TYPE:
        return comparePointer(first.pointerValue, second.pointerValue);
    case NONE_TYPE:
        return 0;
    }
    assert(false);
    return 0;
}

void print(Value value, FILE* destination)
{
    switch (value.type) {
    case INT_TYPE:
        fprintf(destination, "%d", value.intValue);
        break;
    case DOUBLE_TYPE:
        fprintf(destination, "%f", value.doubleValue);
        break;
    case STRING_TYPE:
        fprintf(destination, "%s", value.stringValue);
        break;
    case POINTER_TYPE:
        fprintf(destination, "%p", value.pointerValue);
        break;
    case NONE_TYPE:
        fprintf(destination, "none");
        break;
    }
}
