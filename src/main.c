#include <stdio.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"
#include "menu.h"

int main()
{
    //printf("=== Iniciando Testes do Campeonato de Futebol ===\n\n");

    BDTimes *meu_banco = carregaTimes("data/times.csv");
    BDPartidas *minhas_partidas = carregaPartidas("data/partidas_completo.csv");

    if (meu_banco == NULL)
    {
        printf("Erro Nao foi possivel carregar o banco de times.\n");
        return 1;
    }

    if (minhas_partidas == NULL)
    {
        printf("Erro Nao foi possivel carregar o banco de partidas.\n");
        return 1;
    }

    processaCampeonato(minhas_partidas, meu_banco);
    menu(meu_banco, minhas_partidas);

    printf("Limpando a memoria alocada...\n");
    liberaBDTimes(meu_banco);
    liberarBDPartidas(minhas_partidas);
    printf("Programa encerrado com sucesso!\n");

    return 0;
}
