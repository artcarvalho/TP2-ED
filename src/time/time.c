#include "time.h"
#include <stdlib.h>
#include <string.h>

Time* criaTime(int id, const char *nome){
    Time *t = (Time*) malloc(sizeof(Time)); 

    if(t == NULL){
        return NULL;
    }

    t->id = id;
    t->nome = (char*) malloc(strlen(nome) + 1);
    
    if (t->nome != NULL){
        strcpy(t->nome, nome);   
    }
    
    t->vitorias = 0;
    t->empates  = 0;
    t->derrotas = 0;
    t->gols_marcados=0;
    t->gols_sofridos=0;


    return t;
}

void liberaTime(Time* t) {
    if (t != NULL) {
        free(t->nome); // Libera a string primeiro
        free(t);       // Libera a estrutura depois
    }
}
