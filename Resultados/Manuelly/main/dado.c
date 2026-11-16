//essenciais
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//dado
#include "dado.h"

static unsigned int semente = 2026;

int RolaDado() {
    semente = semente * 1103515245u + 12345u;
    return (int)((semente / 65536u) % FACES_DADO) + 1;
}
