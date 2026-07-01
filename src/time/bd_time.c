#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_time.h"

struct BDTimes
{
    Time *inicio;
    int qtd;
};

BDTimes *criaBDTimes()
{
    BDTimes *bd = (BDTimes *)malloc(sizeof(BDTimes));

    if (bd == NULL)
    {
        return NULL;
    }

    bd->inicio = NULL;
    bd->qtd = 0;

    return bd;
}

static void inserirTimeOrdenado(BDTimes *bd, Time *novo)
{
    if (bd == NULL || novo == NULL)
    {
        return;
    }

    // Mantem a lista de times em ordem crescente de ID.
    if (bd->inicio == NULL || timeGetId(novo) < timeGetId(bd->inicio))
    {
        timeSetProximo(novo, bd->inicio);
        bd->inicio = novo;
        bd->qtd++;
        return;
    }

    Time *atual = bd->inicio;
    while (timeGetProximo(atual) != NULL && timeGetId(timeGetProximo(atual)) < timeGetId(novo))
    {
        atual = timeGetProximo(atual);
    }

    timeSetProximo(novo, timeGetProximo(atual));
    timeSetProximo(atual, novo);
    bd->qtd++;
}

BDTimes *carregaTimes(const char *path)
{
    FILE *a = fopen(path, "r");

    if (a == NULL)
    {
        return NULL;
    }

    BDTimes *bd = criaBDTimes();
    if (bd == NULL)
    {
        fclose(a);
        return NULL;
    }

    char line[256];

    // Ignora o cabecalho do CSV.
    fgets(line, sizeof(line), a);

    while (fgets(line, sizeof(line), a) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';

        char *id_str = strtok(line, ",");
        char *nome = strtok(NULL, ",");

        if (id_str == NULL || nome == NULL)
        {
            continue;
        }

        Time *t = criaTime(atoi(id_str), nome);
        if (t == NULL)
        {
            liberaBDTimes(bd);
            fclose(a);
            return NULL;
        }

        inserirTimeOrdenado(bd, t);
    }

    fclose(a);
    return bd;
}

void liberaBDTimes(BDTimes *bd)
{
    if (bd == NULL)
        return;

    Time *atual = bd->inicio;
    while (atual != NULL)
    {
        Time *proximo = timeGetProximo(atual);
        liberaTime(atual);
        atual = proximo;
    }
    free(bd);
}

Time *buscaTimePorId(BDTimes *bd, int id)
{
    if (bd == NULL || id < 0)
        return NULL;

    for (Time *atual = bd->inicio; atual != NULL; atual = timeGetProximo(atual))
    {
        if (timeGetId(atual) == id)
        {
            return atual;
        }
    }

    return NULL;
}

void reiniciarEstatisticasTimes(BDTimes *bd)
{
    if (bd == NULL)
        return;

    for (Time *atual = bd->inicio; atual != NULL; atual = timeGetProximo(atual))
    {
        timeZerarEstatisticas(atual);
    }
}

void buscaTimes(BDTimes *bd, const char prefixo[50])
{
    if (bd == NULL || prefixo == NULL)
        return;

    int tam_prefixo = strlen(prefixo);
    int encontrado = 0;

    for (Time *atual = bd->inicio; atual != NULL; atual = timeGetProximo(atual))
    {
        if (strncmp(timeGetNome(atual), prefixo, tam_prefixo) == 0)
        {
            if (!encontrado)
            {
                printf("%-4s %-16s %-3s %-3s %-3s %-4s %-4s %-4s %s\n",
                       "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
            }
            printf("%-4d %-16s %-3d %-3d %-3d %-4d %-4d %-4d %d\n",
                   timeGetId(atual), timeGetNome(atual), timeGetVitorias(atual), timeGetEmpates(atual), timeGetDerrotas(atual),
                   timeGetGolsMarcados(atual), timeGetGolsSofridos(atual), obterSaldoGols(atual), obterPontosGanhos(atual));
            encontrado = 1;
        }
    }

    if (!encontrado)
    {
        printf("Nenhum time encontrado com o prefixo \"%s\".\n", prefixo);
    }
}

static int compararTimes(const void *a, const void *b)
{
    Time *ta = *(Time **)a;
    Time *tb = *(Time **)b;

    // Criterios de desempate da classificacao.
    int pa = obterPontosGanhos(ta);
    int pb = obterPontosGanhos(tb);
    if (pa != pb)
        return pb - pa;

    if (timeGetVitorias(ta) != timeGetVitorias(tb))
        return timeGetVitorias(tb) - timeGetVitorias(ta);

    int sa = obterSaldoGols(ta);
    int sb = obterSaldoGols(tb);
    if (sa != sb)
        return sb - sa;

    if (timeGetGolsMarcados(ta) != timeGetGolsMarcados(tb))
        return timeGetGolsMarcados(tb) - timeGetGolsMarcados(ta);

    return timeGetId(ta) - timeGetId(tb);
}

void imprimirTabelaClassificacao(BDTimes *bd)
{
    if (bd == NULL)
        return;

    Time *ordenados[10];
    int total = 0;

    for (Time *atual = bd->inicio; atual != NULL && total < 10; atual = timeGetProximo(atual))
    {
        ordenados[total++] = atual;
    }

    // Ordena apenas os ponteiros, sem mudar a lista original.
    qsort(ordenados, total, sizeof(Time *), compararTimes);

    printf("Imprimindo classificacao...\n\n");
    printf("%-4s %-16s %-3s %-3s %-3s %-4s %-4s %-4s %s\n",
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    for (int i = 0; i < total; i++)
    {
        Time *t = ordenados[i];
        printf("%-4d %-16s %-3d %-3d %-3d %-4d %-4d %-4d %d\n",
               timeGetId(t), timeGetNome(t), timeGetVitorias(t), timeGetEmpates(t), timeGetDerrotas(t),
               timeGetGolsMarcados(t), timeGetGolsSofridos(t), obterSaldoGols(t), obterPontosGanhos(t));
    }
}

void salvarClassificacaoCSV(BDTimes *bd, const char *path)
{
    if (bd == NULL || path == NULL)
        return;

    FILE *f = fopen(path, "w");
    if (f == NULL)
        return;

    Time *ordenados[10];
    int total = 0;

    for (Time *atual = bd->inicio; atual != NULL && total < 10; atual = timeGetProximo(atual))
    {
        ordenados[total++] = atual;
    }

    qsort(ordenados, total, sizeof(Time *), compararTimes);

    fprintf(f, "ID,Time,V,E,D,GM,GS,S,PG\n");
    for (int i = 0; i < total; i++)
    {
        Time *t = ordenados[i];
        fprintf(f, "%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
                timeGetId(t), timeGetNome(t), timeGetVitorias(t), timeGetEmpates(t), timeGetDerrotas(t),
                timeGetGolsMarcados(t), timeGetGolsSofridos(t), obterSaldoGols(t), obterPontosGanhos(t));
    }

    fclose(f);
}
