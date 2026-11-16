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
#include "acao_avanca.h"


struct Avanca{
    int tamanho_avanco_em_casas;
};

Avanca *criaAvanco(int tamanho_avanco_em_casas){
    Avanca * avanco = (Avanca*) calloc(1, sizeof(Avanca));
    avanco->tamanho_avanco_em_casas = tamanho_avanco_em_casas;
    return avanco;
}

Avanca *leAvanco(){
    int avanco=0;
    scanf("%d", &avanco);
    return criaAvanco(avanco);
}

int executaAvanco(void *dado, Jogador *j){
    Avanca * avanco = (Avanca*) dado;
    return avanco->tamanho_avanco_em_casas;
}

void imprimeAvanco(void *dado){
    Avanca * avanco = (Avanca*) dado;
    printf("AVANCA %d", avanco->tamanho_avanco_em_casas);
}

void desalocaAvanco(void *dado){
    Avanca * avanco = (Avanca*) dado;
    free(avanco);
}