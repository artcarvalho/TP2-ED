#ifndef TIME_INTERNAL_H
#define TIME_INTERNAL_H

#include "time.h"

struct Time
{
    int id;
    char *nome;

    int vitorias;
    int empates;
    int derrotas;

    int gols_marcados;
    int gols_sofridos;

    Time *prox;
};

// Cria um time com identificador, nome e estatisticas zeradas.
Time *criaTime(int id, const char *nome);

// Libera a memoria usada por um time.
void liberaTime(Time *t);

// Manipulacao interna da lista e das estatisticas do time.
Time *timeGetProximo(const Time *t);
void timeSetProximo(Time *t, Time *prox);
int timeGetVitorias(const Time *t);
int timeGetEmpates(const Time *t);
int timeGetDerrotas(const Time *t);
int timeGetGolsMarcados(const Time *t);
int timeGetGolsSofridos(const Time *t);
void timeZerarEstatisticas(Time *t);
void timeAdicionarGolsMarcados(Time *t, int gols);
void timeAdicionarGolsSofridos(Time *t, int gols);
void timeAdicionarVitoria(Time *t);
void timeAdicionarEmpate(Time *t);
void timeAdicionarDerrota(Time *t);

#endif
