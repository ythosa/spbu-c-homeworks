#include "./string.h"

typedef struct string {
    uint8_t* data;
    uint8_t length;
    uint8_t capacity;
} str_t;

str_t* stringCreate(uint8_t length)
{
    str_t* s = malloc(sizeof(str_t));

    s->length = length;
    s->data = malloc(length * sizeof(uint8_t));
    s->capacity = 0;

    return s;
}

void stringFree(String s)
{
    free(s->data);
    free(s);
}

uint8_t stringLength(String s)
{
    return s->length;
}

void stringPrint(String s, FILE* dst)
{
    fwrite(s->data, sizeof(uint8_t), s->length, dst);
}

str_t* stringDup(const char* from)
{
    str_t* s = stringCreate(strlen(from));
    memcpy(s->data, from, s->length);
    s->capacity = s->length;

    return s;
}

uint8_t* stringC(String s)
{
    return s->data;
}

str_t* stringCat(String left, String right)
{
    str_t* result = stringCreate(left->length + right->length);

    memcpy(result->data, left->data, left->length);
    memcpy(result->data + left->length, right->data, right->length);
    result->capacity = result->length;

    return result;
}

String stringPush(String s, char c)
{
    String result = stringCreate(s->length + 1);
    memcpy(result->data, s->data, s->length);
    memcpy(result->data + s->length, &c, 1);
    result->capacity = result->length;
    stringFree(s);

    return result;
}

uint8_t stringGet(String s, uint8_t index)
{
    return s->data[index];
}

int stringCmp(String s1, String s2)
{
    return strcmp((const char*)s1->data, (const char*)s2->data);
}
