#include "../dataStructures/dict.h"

#ifndef SPBU_C_HOMEWORKS_CSV_H
#define SPBU_C_HOMEWORKS_CSV_H

/* Prints dictionary into `dst` output in format "<key>,<value>\n...".
 * You need to provide a function that formats dictionary value to String. */
void csvPrintDict(Dict dict, String (*dictValueFormatter)(void*), FILE* dst);

#endif // SPBU_C_HOMEWORKS_CSV_H
