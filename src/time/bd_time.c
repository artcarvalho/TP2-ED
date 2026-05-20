#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "bd_time.h"

BDTimes *criaBDTimes(){
    BDTimes *bd = (BDTimes*) malloc(sizeof(BDTimes));

    if(bd == NULL){
        return NULL;
    }

    for (int i = 0; i < 10; i++) {
        bd->times[i] = NULL;
    }

    bd->qtd = 0;

    return bd;
}

BDTimes *carregaTimes(const char *path){
    FILE *a = fopen(path, "r");

    if(a == NULL){
        return NULL;
    }

    BDTimes *bd = criaBDTimes();
    if (bd == NULL) {
        fclose(a);
        return NULL;
    }

    char line[200];

    fgets(line, sizeof(line), a); //pulando o header do csv

    //fazendo leitura linha a linha dos dados dos times e criando o TAD time com os dados.
    while(fgets(line, 200, a) != NULL){

        int tamanho = strlen(line);

        if (tamanho > 0 && line[tamanho - 1] == '\n') {
            line[tamanho - 1] = '\0';
        }

        int id = atoi(strtok(line, ","));

        char *nome = strtok(NULL, ",");

        Time *t = criaTime(id, nome);

        bd->times[id] = t;
        bd->qtd++;
        
    }
    
    fclose(a);
    return bd;
}

void liberaBDTimes(BDTimes *bd) {
    if (bd == NULL) return;

    for (int i = 0; i < 10; i++) {
        if (bd->times[i] != NULL) {
            liberaTime(bd->times[i]);
        }
    }
    free(bd); 
}

Time* buscaTimePorId(BDTimes *bd, int id) {
    if (bd == NULL || id < 0 || id >= 10) return NULL;
    return bd->times[id]; 
}

void buscaTimes(BDTimes *bd, const char prefixo[50]) {
    if (bd == NULL || prefixo == NULL) return;
    int encontrado = 0;
    int tam_prefixo = strlen(prefixo);

    for (int i = 0; i < 10; i++) {
        if (bd->times[i] != NULL) {
            // Verifica se o nome do time inicia com o prefixo digitado
            if (strncmp(bd->times[i]->nome, prefixo, tam_prefixo) == 0) {
                if (!encontrado) {
                    
                    printf("ID Time\t\t V E D GM GS S PG\n");
                    encontrado = 1;
                }
                Time *t = bd->times[i];
                printf("%d %s\t %4d %4d %4d %4d %4d %4d %4d\n",
                       t->id, t->nome, t->vitorias, t->empates, t->derrotas, t->gols_marcados, t->gols_sofridos,
                       obterSaldoGols(t), obterPontosGanhos(t));
            }
        }
    }
    if (!encontrado) {
        printf("Nenhum time encontrado com o prefixo \"%s\".\n", prefixo);
    }
}

void imprimirTabelaClassificacao(BDTimes *bd) {
    if (bd == NULL) return;
    printf("Imprimindo classificação...\n\n");
    
    printf("%-4s%-16s%-3s%-3s%-3s%-4s%-4s%-4s%s\n", 
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    for (int i = 0; i < 10; i++) {
        if (bd->times[i] != NULL) {
            Time *t = bd->times[i];
            
            printf("%-4d%-16s%-3d%-3d%-3d%-4d%-4d%-4d%d\n",
                   t->id, t->nome, t->vitorias, t->empates, t->derrotas, t->gols_marcados, t->gols_sofridos,
                   obterSaldoGols(t), obterPontosGanhos(t));
        }
    }
}