#include "csv.h"

void csvPrintDict(Dict dict, String (*dictValueFormatter)(void*), FILE* dst)
{
    DictIterator dictIterator = dictIteratorCreate(dict);
    for (Element element = dictIteratorGetNext(dictIterator); element; element = dictIteratorGetNext(dictIterator)) {
        stringPrint(elementGetKey(element), dst);
        fprintf(dst, ",");
        String s = dictValueFormatter(elementGetValue(element));
        stringPrint(s, dst);
        stringFree(s);
        fprintf(dst, "\n");
    }
    dictIteratorFree(dictIterator);
}
