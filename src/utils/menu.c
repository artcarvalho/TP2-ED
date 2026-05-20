#include <stdio.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"

void menu(BDTimes *bd, BDPartidas *bdp)
{
    char escolha;
    char busca[50];
    int n;

    do{
        printf("1 - Consultar time\n2 - Consultar partidas\n3 - Atualizar partida\n4 - Remover partida\n5 - Inserir partida\n6 - Imprimir tabela de classificação\nQ - Sair\n\nEscolha uma opção:");
        scanf(" %c", &escolha);

        switch (escolha){
        case '1':
            system("clear");
            printf("Por favor, insira o nome do time que deseja consultar: ");
            scanf(" %s", busca);
            buscaTimes(bd, busca); 
            break;

        case '2':
            system("clear");
            printf("Escolha o modo de consulta de partida:\n1 - Consulta por time mandante\n2 - Consulta por time visitante\n3 - Consulta por time mandante ou visitante\n4 - Retornar ao menu principal\nOpção: ");
            scanf("%d", &n);
            
            if (n != 4)
            {
                printf("Por favor, insira o nome ou prefixo do time para buscar as partidas: ");
                scanf(" %s", busca);
                

                consultarPartidas(bdp, bd, busca, n); 
            }
            break;

        case '3':
            system("clear");
            printf("Desculpe, Paixão! A função está em outro castelo.\n\n");
            break;

        case '4':
            system("clear");
            printf("Desculpe, Paixão! A função está em outro castelo.\n\n");
            break;

        case '5':
            system("clear");
            printf("Desculpe, Paixão! A função está em outro castelo.\n\n");
            break;

        case '6':
            system("clear");
            imprimirTabelaClassificacao(bd);
            break;

        case 'Q':
            system("clear");
            printf("Saindo do sistema...\n\n");
            break;

        default:
            system("clear");
            printf("Opção inválida!\n\n");
            break;      
        }


        printf("\n");
    } while (escolha != 'Q');
}