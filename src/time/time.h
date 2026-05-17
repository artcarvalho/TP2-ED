#ifndef TIME_H
#define TIME_H

typedef struct{
    int id;
    char *nome;

    int vitorias;
    int empates;
    int derrotas;

    int gols_marcados;
    int gols_sofridos;

} Time;

Time* criarTime(int id, const char *nome);
void liberarTime(Time* t);

#endif