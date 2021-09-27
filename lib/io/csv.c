#include "csv.h"

void csvPrintIntDict(Dict dict, FILE* dst)
{
    for (int i = 0; i < dict->buffer; i++) {
        for (element_t* e = dict->table[i]; e != NULL; e = e->next) {
            stringPrint(e->key, dst);
            fprintf(dst, ";%d\n", *(int*)e->value);
        }
    }
}
