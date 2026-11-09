/*#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"

struct Monstro{
    char * nome;
    int forca, qtd_xp;
};

Monstro *criaMonstro(char *nome, int forca, int xp){
    Monstro * monstro = (Monstro*) calloc(1, sizeof(Monstro));
    monstro->nome = (char*) calloc(MAX_TAM_NOME_MONSTRO, sizeof(char));
    strcpy(monstro->nome, nome);
    monstro->forca = forca;
    monstro->qtd_xp = xp;
    return monstro;
}

Monstro *leMonstro(){
    int forca, xp;
    char nome[MAX_TAM_NOME_MONSTRO];
    scanf(" %[^ ] %d %d", nome, &forca, &xp);
    return criaMonstro(nome, forca, xp);
}

int executaMonstro(void *dado, Jogador *j){
    Monstro * monstro = (Monstro*) dado;
    if(obtemForcaJogador(j) >= monstro->forca){
        adicionaXPJogador(j, monstro->qtd_xp);
        incrementaMonstrosDerrotadosJogador(j);
        return 0;
    }else{
        return RECUO_CELULA;
    }
}

void imprimeMonstro(void *dado){
    Monstro * monstro = (Monstro*) dado;
    printf("MONSTRO %s (F:%d XP:%d)", monstro->nome, monstro->forca, monstro->qtd_xp);
}

void desalocaMonstro(void *dado){
    Monstro * monstro = (Monstro*) dado;
    free(monstro->nome);
    free(monstro);
}
*/