#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

// Definição do tipo BDTimes
typedef struct BDTimes BDTimes;

// Cria um banco de times vazio.
BDTimes *criaBDTimes();

// Libera o banco de times e todos os times armazenados nele.
void liberaBDTimes(BDTimes *bd);

// Carrega os times de um arquivo CSV.
BDTimes *carregaTimes(const char *path);

// Busca um time pelo seu identificador.
Time *buscaTimePorId(BDTimes *bd, int id);

// Reinicia as estatisticas acumuladas de todos os times do banco.
void reiniciarEstatisticasTimes(BDTimes *bd);

// Busca e imprime times cujo nome comece com o prefixo informado.
void buscaTimes(BDTimes *bd, const char prefixo[50]);

// Imprime a tabela de classificacao com os dados atuais dos times.
void imprimirTabelaClassificacao(BDTimes *bd);

// Salva a classificacao atual em um arquivo CSV.
void salvarClassificacaoCSV(BDTimes *bd, const char *path);

#endif
