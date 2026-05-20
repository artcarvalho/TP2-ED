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

/*
 * Cria uma estrutura Partida com os dados informados.
 * id: identificador da partida.
 * idt1: identificador do primeiro time.
 * idt2: identificador do segundo time.
 * gt1: gols marcados pelo primeiro time.
 * gt2: gols marcados pelo segundo time.
 * Retorna a partida preenchida.
 */
Partida criaPartida(int id, int idt1, int idt2, int gt1, int gt2);

#endif
