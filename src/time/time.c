#include "time.h"
#include <stdlib.h>
#include <string.h>

Time* criaTime(int id, const char *nome){
    // Aloca a estrutura do time e copia o nome para memória própria.
    Time *t = (Time*) malloc(sizeof(Time)); 

    if(t == NULL){
        return NULL;
    }

    t->id = id;
    t->nome = (char*) malloc(strlen(nome) + 1);
    
    if (t->nome != NULL){
        strcpy(t->nome, nome);   
    }
    
    // Zera os dados de desempenho; eles serão calculados ao processar as partidas.
    t->vitorias = 0;
    t->empates  = 0;
    t->derrotas = 0;
    t->gols_marcados=0;
    t->gols_sofridos=0;

    return t;
}

void liberaTime(Time* t) {
    // Libera os campos dinâmicos na ordem correta.
    if (t != NULL) {
        free(t->nome); // Libera a string primeiro
        free(t);       // Libera a estrutura depois
    }
}

int obterPontosGanhos(Time *t) {
    // Vitória vale três pontos e empate vale um ponto.
    if (t == NULL) return 0;
    return (t->vitorias * 3) + t->empates; 
}

int obterSaldoGols(Time *t) {
    // O saldo é a diferença entre gols marcados e sofridos.
    if (t == NULL) return 0;
    return t->gols_marcados - t->gols_sofridos;
}
