#include "./string.h"

typedef struct String {
    uint8_t* data;
    uint8_t length;
} str_t;

str_t* stringCreate(uint8_t length)
{
    str_t* s = malloc(sizeof(str_t));

    s->length = length;
    s->data = malloc(length * sizeof(uint8_t) + 1); // + 1 for \0 symbol

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

String stringDup(const char* from)
{
    String s = stringCreate(strlen(from));
    memcpy(s->data, from, s->length + 1); // +1 for copy \0 symbol

    return s;
}

String stringCopy(String from)
{
    String s = stringCreate(from->length);
    memcpy(s->data, from->data, s->length + 1);

    return s;
}

uint8_t* stringC(String s)
{
    return s->data;
}

String stringCat(String left, String right)
{
    String result = stringCreate(left->length + right->length);

    memcpy(result->data, left->data, left->length);
    memcpy(result->data + left->length, right->data, right->length + 1); // +1 for copy \0 symbol

    return result;
}

String stringPush(String s, char c)
{
    String result = stringCreate(s->length + 1);

    memcpy(result->data, s->data, s->length);
    result->data[s->length] = c;
    result->data[s->length + 1] = '\0';

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
