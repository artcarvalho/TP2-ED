#include <stdio.h>
#include <stdlib.h>
#include "bd_time.h"

int main() {
    printf("=== Iniciando Testes do Campeonato de Futebol ===\n\n");

    BDTimes *meu_banco = carregaTimes("data/times.csv");

    if (meu_banco == NULL) {
        printf("Erro Nao foi possivel carregar o banco de times.\n");
        return 1;
    }
    printf("Sucesso: %d times carregados na memoria!\n\n", meu_banco->qtd);


    //printando os times só pra testar
    for(int i = 0; i < 10; i++){
        printf("Time %d %s", meu_banco->times[i]->id, meu_banco->times[i]->nome);
    }

    // 4. Liberação de memória obrigatória antes de fechar o programa
    printf("Limpando a memoria alocada...\n");
    liberarBDTimes(meu_banco);
    printf("Programa encerrado com sucesso!\n");

    return 0;
}