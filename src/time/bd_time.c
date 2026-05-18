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
