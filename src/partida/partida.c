#include "partida.h"
#include <stdlib.h>

struct Partida
{
    int id;
    int id_time1;
    int id_time2;
    int gols_time1;
    int gols_time2;
    // Ponteiro usado para encadear as partidas na lista.
    Partida *prox;
};

Partida *criaPartida(int id, int idt1, int idt2, int gt1, int gt2)
{
    Partida *p = (Partida *)malloc(sizeof(Partida));
    if (p == NULL)
        return NULL;

    p->id = id;
    p->id_time1 = idt1;
    p->id_time2 = idt2;
    p->gols_time1 = gt1;
    p->gols_time2 = gt2;
    p->prox = NULL;

    return p;
}

void liberaPartida(Partida *p)
{
    free(p);
}

int partidaGetId(const Partida *p)
{
    return p != NULL ? p->id : -1;
}

int partidaGetTime1(const Partida *p)
{
    return p != NULL ? p->id_time1 : -1;
}

int partidaGetTime2(const Partida *p)
{
    return p != NULL ? p->id_time2 : -1;
}

int partidaGetGolsTime1(const Partida *p)
{
    return p != NULL ? p->gols_time1 : -1;
}

int partidaGetGolsTime2(const Partida *p)
{
    return p != NULL ? p->gols_time2 : -1;
}

Partida *partidaGetProxima(const Partida *p)
{
    return p != NULL ? p->prox : NULL;
}

void partidaSetGols(Partida *p, int gt1, int gt2)
{
    if (p == NULL)
        return;

    // Atualiza os dois placares juntos para manter a partida consistente.
    p->gols_time1 = gt1;
    p->gols_time2 = gt2;
}

void partidaSetProxima(Partida *p, Partida *prox)
{
    if (p == NULL)
        return;

    p->prox = prox;
}
