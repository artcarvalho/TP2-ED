#include <stdio.h>

void carregaCSV(const char *path){
    FILE *a = fopen(path, "r");

    if(a == NULL){
        return 1;
    }

    
}