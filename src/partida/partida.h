#ifndef PARTIDA_H
#define PARTIDA_H

#include "time.h"

typedef struct
{
    int id;
    int id_time1;
    int id_time2;
    int gols_time1;
    int gols_time2;
} Partida;

Partida criaPartida(int id, int idt1, int idt2, int gt1, int gt2);

#endif