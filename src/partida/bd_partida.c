#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_partida.h"

struct BDPartidas
{
    Partida *inicio;
    int qtd;
};

BDPartidas *criaBDPartidas()
{
    BDPartidas *bd = (BDPartidas *)malloc(sizeof(BDPartidas));
    if (bd == NULL)
        return NULL;

    bd->inicio = NULL;
    bd->qtd = 0;
    return bd;
}

static void inserirPartidaFim(BDPartidas *bd, Partida *nova)
{
    if (bd == NULL || nova == NULL)
        return;

    if (bd->inicio == NULL)
    {
        bd->inicio = nova;
        bd->qtd++;
        return;
    }

    Partida *atual = bd->inicio;
    while (partidaGetProxima(atual) != NULL)
    {
        atual = partidaGetProxima(atual);
    }

    partidaSetProxima(atual, nova);
    bd->qtd++;
}

void liberarBDPartidas(BDPartidas *bd)
{
    if (bd == NULL)
        return;

    Partida *atual = bd->inicio;
    while (atual != NULL)
    {
        Partida *proximo = partidaGetProxima(atual);
        liberaPartida(atual);
        atual = proximo;
    }

    free(bd);
}

BDPartidas *carregaPartidas(const char *path)
{
    FILE *a = fopen(path, "r");
    if (a == NULL)
        return NULL;

    BDPartidas *bd = criaBDPartidas();
    if (bd == NULL)
    {
        fclose(a);
        return NULL;
    }

    char linha[256];
    fgets(linha, sizeof(linha), a);

    while (fgets(linha, sizeof(linha), a) != NULL)
    {
        linha[strcspn(linha, "\r\n")] = '\0';

        char *id_str = strtok(linha, ",");
        char *t1_str = strtok(NULL, ",");
        char *t2_str = strtok(NULL, ",");
        char *g1_str = strtok(NULL, ",");
        char *g2_str = strtok(NULL, ",");

        if (id_str == NULL || t1_str == NULL || t2_str == NULL || g1_str == NULL || g2_str == NULL)
            continue;

        Partida *nova = criaPartida(atoi(id_str), atoi(t1_str), atoi(t2_str), atoi(g1_str), atoi(g2_str));
        if (nova == NULL)
        {
            liberarBDPartidas(bd);
            fclose(a);
            return NULL;
        }

        inserirPartidaFim(bd, nova);
    }

    fclose(a);
    return bd;
}

Partida *buscaPartidaPorId(BDPartidas *bd, int id)
{
    if (bd == NULL || id < 0)
        return NULL;

    for (Partida *atual = bd->inicio; atual != NULL; atual = partidaGetProxima(atual))
    {
        if (partidaGetId(atual) == id)
            return atual;
    }

    return NULL;
}

void consultarPartidas(BDPartidas *bd_partidas, BDTimes *bd_times, const char *nome_busca, int modo)
{
    if (bd_partidas == NULL || bd_times == NULL || nome_busca == NULL)
        return;

    if (modo < 1 || modo > 3)
    {
        printf("Modo de consulta invalido.\n");
        return;
    }

    int encontrado = 0;
    int tam_busca = strlen(nome_busca);

    printf("%-4s %-16s %-16s %-7s %s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");

    for (Partida *atual = bd_partidas->inicio; atual != NULL; atual = partidaGetProxima(atual))
    {
        Time *t1 = buscaTimePorId(bd_times, partidaGetTime1(atual));
        Time *t2 = buscaTimePorId(bd_times, partidaGetTime2(atual));

        if (t1 == NULL || t2 == NULL)
            continue;

        int corresponde = 0;

        if (modo == 1 && strncmp(timeGetNome(t1), nome_busca, tam_busca) == 0)
            corresponde = 1;
        else if (modo == 2 && strncmp(timeGetNome(t2), nome_busca, tam_busca) == 0)
            corresponde = 1;
        else if (modo == 3 && (strncmp(timeGetNome(t1), nome_busca, tam_busca) == 0 || strncmp(timeGetNome(t2), nome_busca, tam_busca) == 0))
            corresponde = 1;

        if (corresponde)
        {
            printf("%-4d %-16s %-16s %-7d %d\n",
                   partidaGetId(atual), timeGetNome(t1), timeGetNome(t2), partidaGetGolsTime1(atual), partidaGetGolsTime2(atual));
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Nenhuma partida encontrada para a busca \"%s\".\n", nome_busca);
    }
}

static int maiorIdPartidas(BDPartidas *bd)
{
    int maior = -1;

    if (bd == NULL)
        return maior;

    for (Partida *atual = bd->inicio; atual != NULL; atual = partidaGetProxima(atual))
    {
        if (partidaGetId(atual) > maior)
            maior = partidaGetId(atual);
    }

    return maior;
}

int inserirPartida(BDPartidas *bd_partidas, BDTimes *bd_times, int id_time1, int id_time2, int gols_time1, int gols_time2)
{
    if (bd_partidas == NULL || bd_times == NULL)
        return 0;

    if (id_time1 == id_time2)
        return 0;

    if (buscaTimePorId(bd_times, id_time1) == NULL || buscaTimePorId(bd_times, id_time2) == NULL)
        return 0;

    Partida *nova = criaPartida(maiorIdPartidas(bd_partidas) + 1, id_time1, id_time2, gols_time1, gols_time2);
    if (nova == NULL)
        return 0;

    inserirPartidaFim(bd_partidas, nova);
    return 1;
}

int atualizarPartida(BDPartidas *bd_partidas, int id_partida, int gols_time1, int gols_time2)
{
    Partida *p = buscaPartidaPorId(bd_partidas, id_partida);
    if (p == NULL)
        return 0;

    partidaSetGols(p, gols_time1, gols_time2);
    return 1;
}

int removerPartida(BDPartidas *bd_partidas, int id_partida)
{
    if (bd_partidas == NULL)
        return 0;

    Partida *anterior = NULL;
    Partida *atual = bd_partidas->inicio;

    while (atual != NULL)
    {
        if (partidaGetId(atual) == id_partida)
        {
            if (anterior == NULL)
                bd_partidas->inicio = partidaGetProxima(atual);
            else
                partidaSetProxima(anterior, partidaGetProxima(atual));

            liberaPartida(atual);
            bd_partidas->qtd--;
            return 1;
        }

        anterior = atual;
        atual = partidaGetProxima(atual);
    }

    return 0;
}

void processaCampeonato(BDPartidas *bd_partidas, BDTimes *bd_times)
{
    if (bd_partidas == NULL || bd_times == NULL)
        return;

    reiniciarEstatisticasTimes(bd_times);

    for (Partida *p = bd_partidas->inicio; p != NULL; p = partidaGetProxima(p))
    {
        Time *t1 = buscaTimePorId(bd_times, partidaGetTime1(p));
        Time *t2 = buscaTimePorId(bd_times, partidaGetTime2(p));

        if (t1 == NULL || t2 == NULL)
            continue;

        timeAdicionarGolsMarcados(t1, partidaGetGolsTime1(p));
        timeAdicionarGolsSofridos(t1, partidaGetGolsTime2(p));
        timeAdicionarGolsMarcados(t2, partidaGetGolsTime2(p));
        timeAdicionarGolsSofridos(t2, partidaGetGolsTime1(p));

        if (partidaGetGolsTime1(p) > partidaGetGolsTime2(p))
        {
            timeAdicionarVitoria(t1);
            timeAdicionarDerrota(t2);
        }
        else if (partidaGetGolsTime1(p) < partidaGetGolsTime2(p))
        {
            timeAdicionarVitoria(t2);
            timeAdicionarDerrota(t1);
        }
        else
        {
            timeAdicionarEmpate(t1);
            timeAdicionarEmpate(t2);
        }
    }
}

void salvarBDPartidasCSV(BDPartidas *bd_partidas, const char *path)
{
    if (bd_partidas == NULL || path == NULL)
        return;

    FILE *f = fopen(path, "w");
    if (f == NULL)
        return;

    fprintf(f, "ID,Time1,Time2,GolsTime1,GolsTime2\n");
    for (Partida *atual = bd_partidas->inicio; atual != NULL; atual = partidaGetProxima(atual))
    {
        fprintf(f, "%d,%d,%d,%d,%d\n",
                partidaGetId(atual), partidaGetTime1(atual), partidaGetTime2(atual), partidaGetGolsTime1(atual), partidaGetGolsTime2(atual));
    }

    fclose(f);
}
