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

/*
 * Cria um time com identificador, nome e estatisticas zeradas.
 * id: identificador do time.
 * nome: nome do time que sera copiado para a estrutura.
 * Retorna um ponteiro para Time alocado dinamicamente, ou NULL em caso de erro.
 */
Time* criaTime(int id, const char *nome);

/*
 * Libera a memoria usada por um time.
 * t: ponteiro para o time que sera liberado.
 */
void liberaTime(Time* t);

/*
 * Calcula os pontos ganhos por um time.
 * t: ponteiro para o time consultado.
 * Retorna 3 pontos por vitoria mais 1 ponto por empate, ou 0 se t for NULL.
 */
int obterPontosGanhos(Time *t);

/*
 * Calcula o saldo de gols de um time.
 * t: ponteiro para o time consultado.
 * Retorna gols marcados menos gols sofridos, ou 0 se t for NULL.
 */
int obterSaldoGols(Time *t);

#endif
