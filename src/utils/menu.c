#include <stdio.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"

void menu(BDTimes *bd, BDPartidas *bdp)
{
    char escolha;
    printf("1 - Consultar time\n2 - Consultar partidas\n3 - Atualizar partida\n4 - Remover partida\n5 - Inserir partida\n6 - Imprimir tabela de classificação\nQ - Sair");
    scanf(" %c", &escolha);

    switch (escolha)
    {
    case '1':
        char busca[50];
        printf("Por favor, insira o nome do time que deseja consultar.");
        scanf(" %s", busca);
        buscaTimes(bd, bdp);
        break;

    case '2':
        char busca[50];
        int n;
        printf("Escolha o modo de consulta de partida:\n1 - Consulta por time mandante\n2 - Consulta por time visitante\n3 - Consulta por time mandante ou visitante\n4 - Retornar ao menu principal");
        scanf("%d", &n);
        if (n != 4)
        {
            buscaPartidas(bdp, bd, busca, n);
        }
        else
        {
            break;
        }
        break;

    case '3':
        printf("Desculpe, Paixão! A função está em outro castelo.");
        break;

    case '4':
        printf("Desculpe, Paixão! A função está em outro castelo.");
        break;

    case '5':
        printf("Desculpe, Paixão! A função está em outro castelo.");
        break;

    case '6':
        printf("Desculpe, Paixão! A função está em outro castelo.");
        break;

    default:
        break;
    }
}