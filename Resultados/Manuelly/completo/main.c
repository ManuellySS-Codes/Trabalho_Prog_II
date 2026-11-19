//essenciais
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//jogo
#include "jogo.h"

int main(){
    Jogo * jogo;
    jogo = CriaJogo();
    jogo = RealizaJogo(jogo);
    DestroiJogo(jogo);
    return 0;
}

