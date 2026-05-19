#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H

#include "partida.h"
#include "bd_time.h"

typedef struct
{
    Partida partidas[150];
    int qtd;
} BDPartidas;

BDPartidas *criaBDPartidas();
void liberarBDPartidas(BDPartidas *bd);
BDPartidas *carregaPartidas(const char *path);
void buscaPartidas(BDPartidas *bdp, BDTimes *bdt, const char *prefixo, int tipoBusca);

#endif