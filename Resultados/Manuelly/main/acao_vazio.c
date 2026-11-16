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
#include "acao_vazio.h"

struct Vazio{
    int tamanho_avanco_em_casas;
};

Vazio *criaVazio(){
    Vazio * vazio = (Vazio*) calloc(1, sizeof(Vazio));
    vazio->tamanho_avanco_em_casas = 0;
    return vazio;
}

Vazio *leVazio(){
    return criaVazio();
}

int executaVazio(void *dado, Jogador *j){
    Vazio * vazio = (Vazio*) dado;
    return vazio->tamanho_avanco_em_casas;
}

void imprimeVazio(void *dado){
    printf("VAZIA");
}

void desalocaVazio(void *dado){
    Vazio * vazio = (Vazio*) dado;
    free(vazio);
}