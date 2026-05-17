#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

typedef struct{
    Time *times;
    int qtd;
} BDTimes;

BDTimes* carregarTimes(const char *path);

#endif