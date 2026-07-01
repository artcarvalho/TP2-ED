#ifndef PARTIDA_INTERNAL_H
#define PARTIDA_INTERNAL_H

#include "partida.h"

struct Partida
{
    int id;
    int id_time1;
    int id_time2;
    int gols_time1;
    int gols_time2;
    Partida *prox;
};

// Cria uma partida com os dados informados e retorna um ponteiro valido.
Partida *criaPartida(int id, int idt1, int idt2, int gt1, int gt2);

// Libera a memoria associada a uma partida.
void liberaPartida(Partida *p);

// Funcoes internas para manipular a lista de partidas.
Partida *partidaGetProxima(const Partida *p);
void partidaSetGols(Partida *p, int gt1, int gt2);
void partidaSetProxima(Partida *p, Partida *prox);

#endif
