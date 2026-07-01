#ifndef PARTIDA_H
#define PARTIDA_H

// Declaracao do tipo Partida.
typedef struct Partida Partida;

// Cria uma partida com os dados informados e retorna um ponteiro valido.
Partida *criaPartida(int id, int idt1, int idt2, int gt1, int gt2);

// Libera a memoria associada a uma partida.
void liberaPartida(Partida *p);

// Funcoes acessoras para respeitar encapsulamento.
int partidaGetId(const Partida *p);
int partidaGetTime1(const Partida *p);
int partidaGetTime2(const Partida *p);
int partidaGetGolsTime1(const Partida *p);
int partidaGetGolsTime2(const Partida *p);

// Funcoes para manipular a lista de partidas.
Partida *partidaGetProxima(const Partida *p);
void partidaSetGols(Partida *p, int gt1, int gt2);
void partidaSetProxima(Partida *p, Partida *prox);

#endif
