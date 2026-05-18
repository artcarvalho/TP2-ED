#include "partida.h"
#include <stdlib.h>
#include <string.h>

Partida criaPartida(int id, int idt1, int idt2, int gt1, int gt2){
    Partida p; 

    p.id = id;
    p.id_time1 = idt1;
    p.id_time2 = idt2;
    p.gols_time1 = gt1;
    p.gols_time2 = gt2;

    return p;
}

