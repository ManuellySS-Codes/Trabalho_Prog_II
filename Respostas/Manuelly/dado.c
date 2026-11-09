#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"
#include "dado.h"

//Nao sei como funciona a avaliacao pra um .h feito por mim
static unsigned int semente = 2026;

int RolaDado() {
    semente = semente * 1103515245u + 12345u;
    return (int)((semente / 65536u) % FACES_DADO) + 1;
}
