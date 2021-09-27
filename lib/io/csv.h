#include "../dataStructures/dict.h"

#ifndef SPBU_C_HOMEWORKS_CSV_H
#define SPBU_C_HOMEWORKS_CSV_H

void csvPrintDict(Dict dict, String (*dictValueFormatter)(void*), FILE* dst);

#endif // SPBU_C_HOMEWORKS_CSV_H
