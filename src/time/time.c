#include "time.h"
#include <stdlib.h>
#include <string.h>

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

Time *criaTime(int id, const char *nome)
{
    Time *t = (Time *)malloc(sizeof(Time));

    if (t == NULL || nome == NULL)
    {
        free(t);
        return NULL;
    }

    t->id = id;
    t->nome = (char *)malloc(strlen(nome) + 1);

    if (t->nome == NULL)
    {
        free(t);
        return NULL;
    }

    strcpy(t->nome, nome);

    t->vitorias = 0;
    t->empates = 0;
    t->derrotas = 0;
    t->gols_marcados = 0;
    t->gols_sofridos = 0;
    t->prox = NULL;

    return t;
}

void liberaTime(Time *t)
{
    if (t != NULL)
    {
        free(t->nome);
        free(t);
    }
}

int timeGetId(const Time *t)
{
    return t != NULL ? t->id : -1;
}

const char *timeGetNome(const Time *t)
{
    return t != NULL ? t->nome : NULL;
}

Time *timeGetProximo(const Time *t)
{
    return t != NULL ? t->prox : NULL;
}

void timeSetProximo(Time *t, Time *prox)
{
    if (t == NULL)
        return;

    t->prox = prox;
}

int timeGetVitorias(const Time *t)
{
    return t != NULL ? t->vitorias : 0;
}

int timeGetEmpates(const Time *t)
{
    return t != NULL ? t->empates : 0;
}

int timeGetDerrotas(const Time *t)
{
    return t != NULL ? t->derrotas : 0;
}

int timeGetGolsMarcados(const Time *t)
{
    return t != NULL ? t->gols_marcados : 0;
}

int timeGetGolsSofridos(const Time *t)
{
    return t != NULL ? t->gols_sofridos : 0;
}

void timeZerarEstatisticas(Time *t)
{
    if (t == NULL)
        return;

    t->vitorias = 0;
    t->empates = 0;
    t->derrotas = 0;
    t->gols_marcados = 0;
    t->gols_sofridos = 0;
}

void timeAdicionarGolsMarcados(Time *t, int gols)
{
    if (t == NULL)
        return;

    t->gols_marcados += gols;
}

void timeAdicionarGolsSofridos(Time *t, int gols)
{
    if (t == NULL)
        return;

    t->gols_sofridos += gols;
}

void timeAdicionarVitoria(Time *t)
{
    if (t == NULL)
        return;

    t->vitorias++;
}

void timeAdicionarEmpate(Time *t)
{
    if (t == NULL)
        return;

    t->empates++;
}

void timeAdicionarDerrota(Time *t)
{
    if (t == NULL)
        return;

    t->derrotas++;
}

int obterPontosGanhos(Time *t)
{
    if (t == NULL)
        return 0;
    return (t->vitorias * 3) + t->empates;
}

int obterSaldoGols(Time *t)
{
    if (t == NULL)
        return 0;
    return t->gols_marcados - t->gols_sofridos;
}
