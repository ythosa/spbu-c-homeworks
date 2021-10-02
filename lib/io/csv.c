#include "csv.h"

void csvPrintDict(Dict dict, String (*dictValueFormatter)(void*), FILE* dst)
{
    for (int i = 0; i < dictGetBufferSize(dict); i++) {
        for (element_t* e = dictGetElementsByIndex(dict, i); e != NULL; e = elementGetNext(e)) {
            stringPrint(elementGetKey(e), dst);
            fprintf(dst, ",");
            String s = dictValueFormatter(elementGetValue(e));
            stringPrint(s, dst);
            stringFree(s);
            fprintf(dst, "\n");
        }
    }
}
