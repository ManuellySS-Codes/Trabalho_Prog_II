#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"

struct Celula{
    Jogador * ocupante;
    func_ptr_executa executa;
    func_ptr_imprime imprime;
    func_ptr_desaloca desaloca;
    void * acao;
};

Celula *criaCelula(void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    Celula * celula = (Celula*) calloc(1, sizeof(Celula));
    if(celula == NULL){
        printf("Nao foi possivel alocar memoria para uma nova celula\n");
        exit(0);
    }
    celula->ocupante = NULL;
    celula->acao = acao;
    celula->executa = executa;
    celula->imprime = imprime;
    celula->desaloca = desaloca;
    return celula;
}

int executaAcaoCelula(Celula *c, Jogador *j){
    return c->executa(c->acao, j);
}

void *obtemAcaoCelula(Celula *c){
    return c->acao;
}

Jogador *obtemOcupanteCelula(Celula *c){
    return c->ocupante;
}

void defineOcupanteCelula(Celula *c, Jogador *j){ //essa funcao tah gerando problema
    c->ocupante = j;
}

int estaOcupadaCelula(Celula *c){
    if(c->ocupante != NULL){
        return 1;
    }
    return 0;
}

void imprimeCelula(Celula *c, int posicao){
    if(posicao == 0){
        printf("[INICIO]\n");
    }else{
        printf("[%d] ",posicao);
        c->imprime(c->acao);
        if(estaOcupadaCelula(c)){
            printf(" <- %s", obtemNomeJogador(c->ocupante));
        }
        printf("\n");
    }
}
 
void desalocaCelula(Celula *c){ 
    c->desaloca(c->acao);
    free(c);
}