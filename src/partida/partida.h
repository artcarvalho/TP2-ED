#ifndef PARTIDA_H
#define PARTIDA_H

// Declaracao do tipo Partida.
typedef struct Partida Partida;

// Funcoes acessoras para respeitar encapsulamento.
int partidaGetId(const Partida *p);
int partidaGetTime1(const Partida *p);
int partidaGetTime2(const Partida *p);
int partidaGetGolsTime1(const Partida *p);
int partidaGetGolsTime2(const Partida *p);

#endif
