#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bd_partida.h"
#include "partida.h"

BDPartidas* criaBDPartidas() {
    BDPartidas *bd = (BDPartidas*) malloc(sizeof(BDPartidas));
    if (bd == NULL) return NULL;

    bd->qtd = 0;
    return bd;
}

void liberarBDPartidas(BDPartidas *bd) {
    if (bd != NULL) {
        free(bd); 
    }
}

BDPartidas* carregaPartidas(const char *path) {
    FILE *a = fopen(path, "r");
    if (a == NULL) {
        return NULL;
    }

    BDPartidas *bd = criaBDPartidas();
    if (bd == NULL) {
        fclose(a);
        return NULL;
    }

    char linha[200];
    fgets(linha, sizeof(linha), a); //pula o cabeçalho do CSV

    while (fgets(linha, sizeof(linha), a) != NULL) {

        int tamanho = strlen(linha);

         if (tamanho > 0 && linha[tamanho - 1] == '\n') {
            linha[tamanho - 1] = '\0';
        }

        char *id_str = strtok(linha, ",");
        char *t1_str = strtok(NULL, ",");
        char *t2_str = strtok(NULL, ",");
        char *g1_str = strtok(NULL, ",");
        char *g2_str = strtok(NULL, ",");

        if (bd->qtd < 150) {
            int id = atoi(id_str);
            int t1 = atoi(t1_str);
            int t2 = atoi(t2_str);
            int g1 = atoi(g1_str);
            int g2 = atoi(g2_str);

            bd->partidas[bd->qtd] = criaPartida(id, t1, t2, g1, g2);
            bd->qtd++;
        }
        
    }

    fclose(a);
    return bd;
}

void consultarPartidas(BDPartidas *bd_partidas, BDTimes *bd_times, const char *nome_busca, int modo) {
    if (bd_partidas == NULL || bd_times == NULL || nome_busca == NULL) return;
    int encontrado = 0;
    int tam_busca = strlen(nome_busca);

    for (int i = 0; i < bd_partidas->qtd; i++) {
        Partida p = bd_partidas->partidas[i];
        
        //Usa a busca por ID para descobrir os nomes das equipes participantes
        Time *t1 = buscaTimePorId(bd_times, p.id_time1);
        Time *t2 = buscaTimePorId(bd_times, p.id_time2);

        if (t1 == NULL || t2 == NULL) continue;

        int corresponde = 0;

        // Filtra os placares dependendo do modo de consulta selecionado pelo usuário
        if (modo == 1 && strncmp(t1->nome, nome_busca, tam_busca) == 0) corresponde = 1;
        else if (modo == 2 && strncmp(t2->nome, nome_busca, tam_busca) == 0) corresponde = 1;
        else if (modo == 3 && (strncmp(t1->nome, nome_busca, tam_busca) == 0 || strncmp(t2->nome, nome_busca, tam_busca) == 0)) {
            corresponde = 1;
        }

        if (corresponde) {
            if (!encontrado) {
                printf("%-3s %-15s %-15s\n", "ID", "Time1", "Time2");
                encontrado = 1;
            }
            printf("%-3d %-15s %d x %d  %-15s\n", p.id, t1->nome, p.gols_time1, p.gols_time2, t2->nome);
        }
    }
    if (!encontrado) {
        printf("Nenhuma partida encontrada para a busca \"%s\".\n", nome_busca);
    }
}

void processaCampeonato(BDPartidas *bd_partidas, BDTimes *bd_times) {
    if (bd_partidas == NULL || bd_times == NULL) return;

    //Distribui os pontos
    for (int i = 0; i < bd_partidas->qtd; i++) {
        Partida p = bd_partidas->partidas[i];
        Time *t1 = buscaTimePorId(bd_times, p.id_time1);
        Time *t2 = buscaTimePorId(bd_times, p.id_time2);

        //Atualiza a quantidade de gols marcados e sofridos de ambos
        t1->gols_marcados += p.gols_time1;
        t1->gols_sofridos += p.gols_time2;
        t2->gols_marcados += p.gols_time2;
        t2->gols_sofridos += p.gols_time1;

        // Avalia as condições para computar Vitórias, Empates e Derrotas
        if (p.gols_time1 > p.gols_time2) {
            t1->vitorias++;
            t2->derrotas++;
        } else if (p.gols_time1 < p.gols_time2) {
            t2->vitorias++;
            t1->derrotas++;
        } else {
            t1->empates++;
            t2->empates++;
        }
    }
}

