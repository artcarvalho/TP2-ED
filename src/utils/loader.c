#include <stdio.h>

void carregaCSV(const char *path){
    // Tenta abrir um CSV genérico; a função ainda não processa o conteúdo.
    FILE *a = fopen(path, "r");

    if(a == NULL){
        return 1;
    }

    
}
