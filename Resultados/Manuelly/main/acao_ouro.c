//essenciais
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//gerais
#include "jogador.h"
#include "celula.h"
#include "mapa.h"
//acoes
#include "acao_ouro.h"

struct Ouro{
    int quantidade_de_ouro;
};

Ouro *criaOuro(int qtd_ouro){
    Ouro * avanco = (Ouro*) calloc(1, sizeof(Ouro));
    avanco->quantidade_de_ouro = qtd_ouro;
    return avanco;
}

Ouro *leOuro(){
    int qtd_ouro=0;
    scanf(" %d", &qtd_ouro);
    return criaOuro(qtd_ouro);
}

int executaOuro(void *dado, Jogador *j){
    Ouro * ouro = (Ouro*) dado;
    adicionaOuroJogador(j, ouro->quantidade_de_ouro);
    return 0;
}

void imprimeOuro(void *dado){
    Ouro * ouro = (Ouro*) dado;
    printf("OURO %d", ouro->quantidade_de_ouro);
}

void desalocaOuro(void *dado){
    Ouro * ouro = (Ouro*) dado;
    free(ouro);
}