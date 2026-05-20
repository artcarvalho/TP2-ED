#ifndef MENU_H
#define MENU_H

/*
 * Exibe o menu principal e direciona as opcoes escolhidas pelo usuario.
 * bd: banco de times usado nas consultas e na tabela de classificacao.
 * bdp: banco de partidas usado nas consultas de jogos.
 */
void menu(BDTimes *bd, BDPartidas *bdp);

#endif
