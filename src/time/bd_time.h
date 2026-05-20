#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

typedef struct
{
    Time *times[10];
    int qtd;
} BDTimes;

BDTimes *criaBDTimes();
BDTimes *carregaTimes(const char *path);

void liberaBDTimes(BDTimes *bd);
BDTimes *carregaTimes(const char *path);
Time *buscaTimePorId(BDTimes *bd, int id);

void buscaTimes(BDTimes *bd, const char prefixo[50]);
void imprimirTabelaClassificacao(BDTimes *bd);

#endif