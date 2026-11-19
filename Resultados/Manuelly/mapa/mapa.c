//essenciais
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//gerais
#include "jogador.h"
#include "celula.h"
#include "mapa.h"
#include "acao_monstro.h"

struct Mapa{
    int qtd_celulas; // Quantidade de celulas informadas n
    Celula **celulas; // Vetor de tamanho N casas 1 a n
};

Mapa *criaMapa(){
    Mapa *m = (Mapa*) calloc(1, sizeof(Mapa));
    m->qtd_celulas = 0;
    m->celulas = NULL;
    return m;
}

void insereCelulaMapa(Mapa *m, void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    m->qtd_celulas++;
    m->celulas = (Celula**) realloc(m->celulas, m->qtd_celulas * sizeof(Celula*)); //aumentando o tamanho do vetor
    // Insere a nova celula na ultima posicao do vetor
    m->celulas[m->qtd_celulas - 1] = criaCelula(acao, executa, imprime, desaloca); //inserindo a celula nova na posicao mais recente do vetor
}

int obtemQtdCelulasMapa(Mapa *m){
    return m->qtd_celulas;
}

int obtemPosicaoFimMapa(Mapa *m){
    return m->qtd_celulas + 1; //soma n com 1
}

Celula *obtemCelulaMapa(Mapa *m, int posicao){
    // Casas de 1 a N correspondem aos indices 0 a n menos 1 do vetor
    if (posicao < 1 || posicao > m->qtd_celulas) {
        return NULL;
    }
    return m->celulas[posicao - 1]; 
}

Jogador *obtemOcupanteMapa(Mapa *m, int posicao){
    Celula *c = obtemCelulaMapa(m, posicao);
    if (c == NULL){
        return NULL;
    }
    return obtemOcupanteCelula(c);
}

void retiraJogadorMapa(Mapa *m, Jogador *j){
    int pos = obtemPosicaoJogador(j);
    if (pos >= 1 && pos <= m->qtd_celulas){ //verifica se a posicao do jogador estah dentro do vetor de celulas
        Celula * c = obtemCelulaMapa(m, pos); 
        if(c != NULL && obtemOcupanteCelula(c) == j){ //verifica se o jogador do cabecalho que esta realmente ocupando a celula passada
            defineOcupanteCelula(c, NULL); //define que o ocupante eh nulo pra tirar ponteiro do jogador que tava la
        }
    }
}

void moveJogadorMapa(Mapa *m, Jogador *j, int posicao){
    retiraJogadorMapa(m, j);

    definePosicaoJogador(j, posicao); //atualiza a posicao do jogador
    
    if (posicao > 0 && posicao <= m->qtd_celulas) { //verifica se eh uma celula valida dentro do vetor de celulas antes de colocar o jogador na casa
        Celula *c = obtemCelulaMapa(m, posicao);
        defineOcupanteCelula(c, j);
    }
}

void recuaJogadorMapa(Mapa *m, Jogador *j, int origem){
    int posicao_atual = origem - 1; //a primeira posicao a ser testada eh a anterior ah origem

    while(posicao_atual >= 0){
        if(!estaOcupadaCelula(m->celulas[posicao_atual])){ //se a posicao nao esta ocupada move o jogador pra ela
            moveJogadorMapa(m, j, posicao_atual + 1);
            return;
        }
        posicao_atual--;
    }
    moveJogadorMapa(m, j, 0); // Vai para o inicio se tudo estiver ocupado
}

void imprimeCelulasMapa(Mapa *m){
    for(int i = 0; i < m->qtd_celulas; i++){
        if (m->celulas[i] != NULL){
            imprimeCelula(m->celulas[i], i + 1);
        }
    }
}

void desalocaMapa(Mapa *m){
    for(int i = 0; i < m->qtd_celulas; i++){
        if(m->celulas[i] != NULL){
            desalocaCelula(m->celulas[i]);
        }
    }
    if(m->celulas != NULL){
        free(m->celulas);
    }
    free(m);
}