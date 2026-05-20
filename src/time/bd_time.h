#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

typedef struct
{
    Time *times[10];
    int qtd;
} BDTimes;

/*
 * Cria um banco de times vazio.
 * Retorna um ponteiro para BDTimes alocado dinamicamente, ou NULL em caso de erro.
 */
BDTimes *criaBDTimes();

/*
 * Carrega os times de um arquivo CSV.
 * path: caminho do arquivo que contem os dados dos times.
 * Retorna um ponteiro para o banco preenchido, ou NULL se nao conseguir carregar.
 */
BDTimes *carregaTimes(const char *path);

/*
 * Libera o banco de times e todos os times armazenados nele.
 * bd: ponteiro para o banco que sera liberado.
 */
void liberaBDTimes(BDTimes *bd);

/*
 * Carrega os times de um arquivo CSV.
 * path: caminho do arquivo que contem os dados dos times.
 * Retorna um ponteiro para o banco preenchido, ou NULL se nao conseguir carregar.
 */
BDTimes *carregaTimes(const char *path);

/*
 * Busca um time pelo seu identificador.
 * bd: banco de times consultado.
 * id: identificador do time desejado.
 * Retorna o ponteiro para o time encontrado, ou NULL se o banco/id for invalido.
 */
Time *buscaTimePorId(BDTimes *bd, int id);

/*
 * Busca e imprime times cujo nome comece com o prefixo informado.
 * bd: banco de times consultado.
 * prefixo: inicio do nome usado como filtro.
 */
void buscaTimes(BDTimes *bd, const char prefixo[50]);

/*
 * Imprime a tabela de classificacao com os dados atuais dos times.
 * bd: banco de times que sera percorrido.
 */
void imprimirTabelaClassificacao(BDTimes *bd);

#endif
