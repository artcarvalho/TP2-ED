#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H

#include "partida.h"
#include "bd_time.h" 

typedef struct {
    Partida partidas[150]; 
    int qtd;                        
} BDPartidas;

BDPartidas* criaBDPartidas();
void liberarBDPartidas(BDPartidas *bd);
BDPartidas* carregaPartidas(const char *path);


void consultarPartidas(BDPartidas *bd_partidas, BDTimes *bd_times, const char *nome_busca, int modo);
void processaCampeonato(BDPartidas *bd_partidas, BDTimes *bd_times);

#endif