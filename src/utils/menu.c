#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_time.h"
#include "bd_partida.h"

static const char *ARQ_PARTIDAS_BD = "data/bd_partidas.csv";
static const char *ARQ_CLASSIFICACAO_BD = "data/bd_classificacao.csv";

static void limparEntradaRestante(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

static int lerInteiro(const char *n, int *valor)
{
    if (n != NULL)
        printf("%s", n);

    if (scanf("%d", valor) != 1)
    {
        limparEntradaRestante();
        return 0;
    }

    return 1;
}

static int lerCampoOpcional(const char *prompt, int atual, int *valor)
{
    char buffer[32];

    if (prompt != NULL)
        printf("%s", prompt);

    if (scanf("%31s", buffer) != 1)
    {
        limparEntradaRestante();
        return 0;
    }

    if (strcmp(buffer, "-") == 0)
    {
        // O hifen indica que o valor antigo deve ser mantido.
        *valor = atual;
        return 1;
    }

    char *fim = NULL;
    long convertido = strtol(buffer, &fim, 10);
    if (fim == buffer || *fim != '\0')
        return 0;

    *valor = (int)convertido;
    return 1;
}

static const char *nomeOuHifen(Time *t)
{
    const char *nome = timeGetNome(t);
    return nome != NULL ? nome : "-";
}

static void recalcularEClassificar(BDPartidas *bdp, BDTimes *bd)
{
    // Sempre salva os CSVs depois que uma partida muda.
    processaCampeonato(bdp, bd);
    salvarBDPartidasCSV(bdp, ARQ_PARTIDAS_BD);
    salvarClassificacaoCSV(bd, ARQ_CLASSIFICACAO_BD);
}

void menu(BDTimes *bd, BDPartidas *bdp)
{
    char escolha = '\0';

    do
    {
        printf("\n========= Sistema de Gerenciamento de Partidas =========\n");
        printf("1 - Consultar time\n");
        printf("2 - Consultar partidas\n");
        printf("3 - Atualizar partida\n");
        printf("4 - Remover partida\n");
        printf("5 - Inserir partida\n");
        printf("6 - Imprimir tabela de classificacao\n");
        printf("Q - Sair\n");

        printf("Escolha uma opcao: ");
        if (scanf(" %c", &escolha) != 1)
        {
            limparEntradaRestante();
            escolha = 'Q';
        }

        switch (escolha)
        {
        case '1':
        {
            char busca[50];
            printf("Digite o nome ou prefixo do time: ");
            if (scanf("%49s", busca) == 1)
            {
                buscaTimes(bd, busca);
            }
            else
            {
                limparEntradaRestante();
            }
            break;
        }

        case '2':
        {
            char busca[50];
            int modo;

            printf("Escolha o modo de consulta de partida:\n");
            printf("1 - Consulta por time mandante\n");
            printf("2 - Consulta por time visitante\n");
            printf("3 - Consulta por time mandante ou visitante\n");
            printf("4 - Retornar ao menu principal\n");

            if (!lerInteiro("Opcao: ", &modo))
                break;

            if (modo == 4)
                break;

            printf("Digite o nome ou prefixo do time: ");
            if (scanf("%49s", busca) == 1)
            {
                consultarPartidas(bdp, bd, busca, modo);
            }
            else
            {
                limparEntradaRestante();
            }
            break;
        }

        case '3':
        {
            char busca[50];
            int modo;
            int id_partida;
            int novo_g1;
            int novo_g2;

            printf("Escolha o modo de consulta de partida:\n");
            printf("1 - Consulta por time mandante\n");
            printf("2 - Consulta por time visitante\n");
            printf("3 - Consulta por time mandante ou visitante\n");
            printf("4 - Retornar ao menu principal\n");

            if (!lerInteiro("Opcao: ", &modo) || modo == 4)
                break;

            printf("Digite o nome ou prefixo do time: ");
            if (scanf("%49s", busca) != 1)
            {
                limparEntradaRestante();
                break;
            }

            consultarPartidas(bdp, bd, busca, modo);

            if (!lerInteiro("Digite o ID do registro a ser atualizado: ", &id_partida))
                break;

            Partida *p = buscaPartidaPorId(bdp, id_partida);
            if (p == NULL)
            {
                printf("Registro nao encontrado.\n");
                break;
            }

            printf("Digite o novo valor para os campos Placar1 e Placar2 (para manter o valor atual de um campo, digite '-').\n");
            if (!lerCampoOpcional("Placar1: ", partidaGetGolsTime1(p), &novo_g1))
                break;
            if (!lerCampoOpcional("Placar2: ", partidaGetGolsTime2(p), &novo_g2))
                break;

            printf("\nConfirma os novos valores para o registro abaixo? (S/N)\n");
            Time *t1 = buscaTimePorId(bd, partidaGetTime1(p));
            Time *t2 = buscaTimePorId(bd, partidaGetTime2(p));
            printf("%-4s %-16s %-16s %-7s %s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
            printf("%-4d %-16s %-16s %-7d %d\n", partidaGetId(p), nomeOuHifen(t1), nomeOuHifen(t2), novo_g1, novo_g2);

            char confirma;
            if (scanf(" %c", &confirma) != 1)
            {
                limparEntradaRestante();
                break;
            }

            if (confirma == 'S' || confirma == 's')
            {
                if (atualizarPartida(bdp, id_partida, novo_g1, novo_g2))
                {
                    recalcularEClassificar(bdp, bd);
                    printf("Registro atualizado com sucesso.\n");
                }
                else
                {
                    printf("Nao foi possivel atualizar o registro.\n");
                }
            }
            break;
        }

        case '4':
        {
            char busca[50];
            int modo;
            int id_partida;

            printf("Escolha o modo de consulta de partida:\n");
            printf("1 - Consulta por time mandante\n");
            printf("2 - Consulta por time visitante\n");
            printf("3 - Consulta por time mandante ou visitante\n");
            printf("4 - Retornar ao menu principal\n");

            if (!lerInteiro("Opcao: ", &modo) || modo == 4)
                break;

            printf("Digite o nome ou prefixo do time: ");
            if (scanf("%49s", busca) != 1)
            {
                limparEntradaRestante();
                break;
            }

            consultarPartidas(bdp, bd, busca, modo);

            if (!lerInteiro("Digite o ID do registro a ser removido: ", &id_partida))
                break;

            Partida *p = buscaPartidaPorId(bdp, id_partida);
            if (p == NULL)
            {
                printf("Registro nao encontrado.\n");
                break;
            }

            Time *t1 = buscaTimePorId(bd, partidaGetTime1(p));
            Time *t2 = buscaTimePorId(bd, partidaGetTime2(p));
            printf("\nTem certeza de que deseja excluir o registro abaixo? (S/N)\n");
            printf("%-4s %-16s %-16s %-7s %s\n", "ID", "Time1", "Time2", "Placar1", "Placar2");
            printf("%-4d %-16s %-16s %-7d %d\n", partidaGetId(p), nomeOuHifen(t1), nomeOuHifen(t2), partidaGetGolsTime1(p), partidaGetGolsTime2(p));

            char confirma;
            if (scanf(" %c", &confirma) != 1)
            {
                limparEntradaRestante();
                break;
            }

            if (confirma == 'S' || confirma == 's')
            {
                if (removerPartida(bdp, id_partida))
                {
                    recalcularEClassificar(bdp, bd);
                    printf("Registro removido com sucesso.\n");
                }
                else
                {
                    printf("Nao foi possivel remover o registro.\n");
                }
            }
            break;
        }

        case '5':
        {
            int t1, t2, g1, g2;
            char confirma;
            Time *time1;
            Time *time2;

            printf("Para inserir um novo registro, digite os valores para os campos Time1, Time2, Placar1 e Placar2.\n");
            if (!lerInteiro("Time1: ", &t1))
                break;
            if (!lerInteiro("Time2: ", &t2))
                break;
            if (!lerInteiro("Placar1: ", &g1))
                break;
            if (!lerInteiro("Placar2: ", &g2))
                break;

            time1 = buscaTimePorId(bd, t1);
            time2 = buscaTimePorId(bd, t2);
            if (time1 == NULL || time2 == NULL || t1 == t2)
            {
                printf("Nao foi possivel inserir o registro.\n");
                break;
            }

            printf("\nConfirma a insercao do registro abaixo? (S/N)\n");
            printf("%-16s %-16s %-7s %s\n", "Time1", "Time2", "Placar1", "Placar2");
            printf("%-16s %-16s %-7d %d\n", nomeOuHifen(time1), nomeOuHifen(time2), g1, g2);

            if (scanf(" %c", &confirma) != 1)
            {
                limparEntradaRestante();
                break;
            }

            if (confirma == 'S' || confirma == 's')
            {
                if (inserirPartida(bdp, bd, t1, t2, g1, g2))
                {
                    recalcularEClassificar(bdp, bd);
                    printf("O registro foi inserido com sucesso.\n");
                }
                else
                {
                    printf("Nao foi possivel inserir o registro.\n");
                }
            }
            break;
        }

        case '6':
            imprimirTabelaClassificacao(bd);
            break;

        case 'Q':
        case 'q':
            printf("Saindo do sistema...\n");
            break;

        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (escolha != 'Q' && escolha != 'q');
}
