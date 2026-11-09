#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"

struct Mapa{
    int qtd_celulas; // Quantidade de células informadas (N)
    Celula **celulas; // Vetor de tamanho N (índices de 0 a N-1 para as casas 1 a N)
};

Mapa *criaMapa(){
    Mapa *m = (Mapa*) calloc(1, sizeof(Mapa));
    m->qtd_celulas = 0;
    m->celulas = NULL; //cada celula sera alocada dinamicamente
    return m;
}
//comentar melhor as funcoes

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
    return m->qtd_celulas + 1; // Fim eh N + 1
}

Celula *obtemCelulaMapa(Mapa *m, int posicao){
    // Casas de 1 a N correspondem aos índices 0 a N-1 do vetor
    if (posicao < 1 || posicao > m->qtd_celulas) {
        return NULL; // Início (0), Fim ou inválidas retornam NULL
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
    if (pos >= 1 && pos <= m->qtd_celulas) { //se a posicao for valida
        Celula * c = obtemCelulaMapa(m, pos); 
        if(c != NULL && obtemOcupanteCelula(c) == j){ 
            defineOcupanteCelula(c, NULL); //define que o ocupante eh nulo pra tirar ponteiro do jogador que tava lah
        }
    }
}

void moveJogadorMapa(Mapa *m, Jogador *j, int posicao){
    retiraJogadorMapa(m, j);
    definePosicaoJogador(j, posicao); //atualiza a posicao do jogador
    
    if (posicao > 0 && posicao <= m->qtd_celulas) { //verificando se a casa tah dentro do vetor de celulas pra poder definir o ocupante da celula valida
        Celula *c = obtemCelulaMapa(m, posicao);
        defineOcupanteCelula(c, j); //soh usa essa funcao se for dentro de uma celula valida dentro da celula inicio ou fim nao eh
    }
}

void recuaJogadorMapa(Mapa *m, Jogador *j, int origem){
    int posicao_atual = origem - 1; //jogador comeca tentando recusar pra casa anterior a de origem
    
    while(posicao_atual > 0){
        if(!estaOcupadaCelula(m->celulas[posicao_atual])){
            moveJogadorMapa(m, j, posicao_atual);
            return;
        }
        posicao_atual--;
    }
    moveJogadorMapa(m, j, 0); //jogador vai pra casa inicial se nao encontrou nenhuma desocupada na regra de recuo
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