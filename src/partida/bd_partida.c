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
    fgets(linha, sizeof(linha), a); // Consome e pula o cabeçalho (header) do CSV

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

