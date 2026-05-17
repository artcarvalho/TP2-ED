#ifndef TIME_H
#define TIME_H

typedef struct{
    int id;
    char nome[50];

    int vitorias;
    int empates;
    int derrotas;

    int gols_marcados;
    int gols_sofridos;

} Time;

Time* criarTime();

#endif