#include "csv.h"

void csvPrintDict(Dict dict, String (*dictValueFormatter)(void*), FILE* dst)
{
    for (int i = 0; i < dict->buffer; i++) {
        for (element_t* e = dict->table[i]; e != NULL; e = e->next) {
            stringPrint(e->key, dst);
            fprintf(dst, ";");
            String s = dictValueFormatter(e->value);
            stringPrint(s, dst);
            stringFree(s);
            fprintf(dst, "\n");
        }
    }
}
