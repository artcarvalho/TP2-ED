#ifndef PARTIDA_H
#define PARTIDA_H

#include "time.h"

typedef struct{
    int id;

    int id_time1;
    int id_time2;

    int gols_time1;
    int gols_time2;
} Partida;

void calculaEstatisticas(Partida *p);

#endif