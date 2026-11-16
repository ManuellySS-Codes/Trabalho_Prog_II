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
#include "acao_volta.h"

struct Volta{
    int tamanho_avanco_em_casas;
};

Volta *criaVolta(int tamanho_avanco_em_casas){
    Volta * avanco = (Volta*) calloc(1, sizeof(Volta));
    avanco->tamanho_avanco_em_casas = tamanho_avanco_em_casas;
    return avanco;
}

Volta *leVolta(){
    int volta=0;
    scanf(" %d", &volta);
    return criaVolta(volta);
}

int executaVolta(void *dado, Jogador * j){
    Volta * volta = (Volta*) dado;
    return (-(volta->tamanho_avanco_em_casas)); //avanco negativo porque eh para voltar casas
}

void imprimeVolta(void *dado){
    Volta * volta = (Volta*) dado;
    printf("VOLTA %d", volta->tamanho_avanco_em_casas);
}

void desalocaVolta(void *dado){
    Volta * volta = (Volta*) dado;
    free(volta);
}