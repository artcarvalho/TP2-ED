#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H

#include "partida.h"
#include "bd_time.h"

// Definição do tipo BDPartidas
typedef struct BDPartidas BDPartidas;

// Cria um banco de partidas vazio.
BDPartidas *criaBDPartidas();

// Libera a memoria usada pelo banco de partidas.
void liberarBDPartidas(BDPartidas *bd);

// Carrega as partidas de um arquivo CSV.
BDPartidas *carregaPartidas(const char *path);

// Busca uma partida pelo seu identificador.
Partida *buscaPartidaPorId(BDPartidas *bd, int id);

// Consulta e imprime partidas que correspondem ao nome ou prefixo informado.
void consultarPartidas(BDPartidas *bd_partidas, BDTimes *bd_times, const char *nome_busca, int modo);

// Insere uma nova partida no fim da lista, validando os times informados.
int inserirPartida(BDPartidas *bd_partidas, BDTimes *bd_times, int id_time1, int id_time2, int gols_time1, int gols_time2);

// Atualiza o placar de uma partida existente.
int atualizarPartida(BDPartidas *bd_partidas, int id_partida, int gols_time1, int gols_time2);

// Remove uma partida existente da lista.
int removerPartida(BDPartidas *bd_partidas, int id_partida);

// Processa todas as partidas e atualiza a classificacao dos times.
void processaCampeonato(BDPartidas *bd_partidas, BDTimes *bd_times);

// Salva o banco atual de partidas em um arquivo CSV.
void salvarBDPartidasCSV(BDPartidas *bd_partidas, const char *path);

#endif
