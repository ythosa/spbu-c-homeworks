#ifndef SPBU_C_HOMEWORKS_VALUES_H
#define SPBU_C_HOMEWORKS_VALUES_H

#include <stdbool.h>

typedef enum ValueType {
    INT_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    POINTER_TYPE,
    NONE_TYPE
} ValueType;

#pragma pack(push, 4)
typedef struct Value {
    enum ValueType type;
    union {
        int intValue;
        double doubleValue;
        char* stringValue;
        void* pointerValue;
    };
} Value;
#pragma pack(pop)

typedef int (*Comparator)(Value, Value);

Value wrapInt(int value);
Value wrapDouble(double value);
Value wrapString(char* value);
Value wrapPointer(void* value);
Value wrapNone();

int getInt(Value value);
double getDouble(Value value);
char* getString(Value value);
void* getPointer(Value value);
bool isNone(Value value);

bool equals(Value first, Value second);
int compare(Value first, Value second);

#endif // SPBU_C_HOMEWORKS_VALUES_H
