#include <stdio.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"
#include "menu.h"

int main()
{
    //printf("=== Iniciando Testes do Campeonato de Futebol ===\n\n");

    // Carrega os dados iniciais usados durante toda a execução do programa.
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

    // Calcula a classificação antes de exibir o menu principal.
    processaCampeonato(minhas_partidas, meu_banco);
    menu(meu_banco, minhas_partidas);

    // Libera os bancos alocados antes de encerrar o programa.
    printf("Limpando a memoria alocada...\n");
    liberaBDTimes(meu_banco);
    liberarBDPartidas(minhas_partidas);
    printf("Programa encerrado com sucesso!\n");

    return 0;
}
