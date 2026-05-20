#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H

#include "partida.h"
#include "bd_time.h"

typedef struct
{
    Partida partidas[150];
    int qtd;
} BDPartidas;

/*
 * Cria um banco de partidas vazio.
 * Retorna um ponteiro para BDPartidas alocado dinamicamente, ou NULL em caso de erro.
 */
BDPartidas *criaBDPartidas();

/*
 * Libera a memoria usada pelo banco de partidas.
 * bd: ponteiro para o banco que sera liberado.
 */
void liberarBDPartidas(BDPartidas *bd);

/*
 * Carrega as partidas de um arquivo CSV.
 * path: caminho do arquivo que contem os dados das partidas.
 * Retorna um ponteiro para o banco preenchido, ou NULL se nao conseguir carregar.
 */
BDPartidas *carregaPartidas(const char *path);

/*
 * Busca partidas usando um prefixo de nome de time e um tipo de busca.
 * bdp: banco de partidas consultado.
 * bdt: banco de times usado para relacionar IDs aos nomes.
 * prefixo: inicio do nome usado como filtro.
 * tipoBusca: define se a busca considera mandante, visitante ou ambos.
 */
void buscaPartidas(BDPartidas *bdp, BDTimes *bdt, const char *prefixo, int tipoBusca);

/*
 * Consulta e imprime partidas que correspondem ao nome ou prefixo informado.
 * bd_partidas: banco com as partidas carregadas.
 * bd_times: banco com os times carregados.
 * nome_busca: nome ou prefixo usado para filtrar os times.
 * modo: define se a busca sera por time mandante, visitante ou qualquer um dos dois.
 */
void consultarPartidas(BDPartidas *bd_partidas, BDTimes *bd_times, const char *nome_busca, int modo);

/*
 * Processa todas as partidas e atualiza a classificacao dos times.
 * bd_partidas: banco com os placares das partidas.
 * bd_times: banco de times que recebera vitorias, empates, derrotas e gols.
 */
void processaCampeonato(BDPartidas *bd_partidas, BDTimes *bd_times);

#endif
