#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H


#include "partida.h"

typedef struct{
    Partida *Partidas[45];
    int qtd;
} BDPartidas;

Partida * carregaPartida(const char *path);

Partida* criaBDPartida();

void LiberaBDPartidas(BDTimes *bd);

#endif