#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

typedef struct{
    Time *times[10];
    int qtd;
} BDTimes;

BDTimes* carregaTimes(const char *path);

BDTimes* criaBDTimes();

void liberarBDTimes(BDTimes *bd);

#endif