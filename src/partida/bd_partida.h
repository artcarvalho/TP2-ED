#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H


#include "partida.h"

typedef struct{
    Partida *Partidas;
    int qtd;
} BDPartidas;

void carregaPartida(const char *path);


#endif