#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

typedef struct{
    Time *times[10];
    int qtd;
} BDTimes;

BDTimes* criaBDTimes();
void liberaBDTimes(BDTimes *bd);
BDTimes* carregaTimes(const char *path);
Time* buscaTimePorId(BDTimes *bd, int id);

void buscaTimes(const char *busca, BDTimes *bd);
void imprimirTabelaClassificacao(BDTimes *bd);

#endif