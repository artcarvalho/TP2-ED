#ifndef TIME_H
#define TIME_H

// Definição do type Time
typedef struct Time Time;

// Cria um time com identificador, nome e estatisticas zeradas.
Time *criaTime(int id, const char *nome);

// Libera a memoria usada por um time.
void liberaTime(Time *t);

// Acesso aos campos publicos do time sem expor a estrutura completa no .h.
int timeGetId(const Time *t);
const char *timeGetNome(const Time *t);

// Manipulacao da lista e das estatisticas do time.
Time *timeGetProximo(const Time *t);
void timeSetProximo(Time *t, Time *prox);
int timeGetVitorias(const Time *t);
int timeGetEmpates(const Time *t);
int timeGetDerrotas(const Time *t);
int timeGetGolsMarcados(const Time *t);
int timeGetGolsSofridos(const Time *t);
void timeZerarEstatisticas(Time *t);
void timeAdicionarGolsMarcados(Time *t, int gols);
void timeAdicionarGolsSofridos(Time *t, int gols);
void timeAdicionarVitoria(Time *t);
void timeAdicionarEmpate(Time *t);
void timeAdicionarDerrota(Time *t);

// Calcula os pontos ganhos por um time.
int obterPontosGanhos(Time *t);

// Calcula o saldo de gols de um time.
int obterSaldoGols(Time *t);

#endif
