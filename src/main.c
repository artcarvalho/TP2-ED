#include <stdio.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"

int main()
{
    printf("=== Iniciando Testes do Campeonato de Futebol ===\n\n");

    BDTimes *meu_banco = carregaTimes("data/times.csv");
    BDPartidas *minhas_partidas = carregaPartidas("data/partidas_completo.csv");

    if (meu_banco == NULL)
    {
        printf("Erro Nao foi possivel carregar o banco de times.\n");
        return 1;
    }
    printf("Sucesso: %d times carregados na memoria!\n\n", meu_banco->qtd);

    if (minhas_partidas == NULL)
    {
        printf("Erro Nao foi possivel carregar o banco de partidas.\n");
        return 1;
    }

    menu();

    // printando os times só pra testar
    for (int i = 0; i < 10; i++)
    {
        printf("Time %d %s\n", meu_banco->times[i]->id, meu_banco->times[i]->nome);
    }

    for (int j = 0; j < minhas_partidas->qtd; j++)
    {
        printf(
            "Partida %d: %d %d X %d %d\n",
            minhas_partidas->partidas[j].id,
            minhas_partidas->partidas[j].id_time1,
            minhas_partidas->partidas[j].gols_time1,
            minhas_partidas->partidas[j].id_time2,
            minhas_partidas->partidas[j].gols_time2);
    }

    // 4. Liberação de memória obrigatória antes de fechar o programa
    printf("Limpando a memoria alocada...\n");
    liberaBDTimes(meu_banco);
    liberarBDPartidas(minhas_partidas);
    printf("Programa encerrado com sucesso!\n");

    return 0;
}
