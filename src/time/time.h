#ifndef TIME_H
#define TIME_H

// Definição do type Time
typedef struct Time Time;

// Acesso aos campos publicos do time sem expor a estrutura completa no .h.
int timeGetId(const Time *t);
const char *timeGetNome(const Time *t);

// Calcula os pontos ganhos por um time.
int obterPontosGanhos(Time *t);

// Calcula o saldo de gols de um time.
int obterSaldoGols(Time *t);

#endif
