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
    m->celulas = NULL;
    return m;
}

void insereCelulaMapa(Mapa *m, void *acao, func_ptr_executa executa, func_ptr_imprime imprime, func_ptr_desaloca desaloca){
    m->qtd_celulas++;
    m->celulas = (Celula**) realloc(m->celulas, m->qtd_celulas * sizeof(Celula*));
    // Insere a nova célula na última posição do vetor
    m->celulas[m->qtd_celulas - 1] = criaCelula(acao, executa, imprime, desaloca);
}

int obtemQtdCelulasMapa(Mapa *m){
    return m->qtd_celulas;
}

int obtemPosicaoFimMapa(Mapa *m){
    return m->qtd_celulas + 1; // Fim é N + 1
}

Celula *obtemCelulaMapa(Mapa *m, int posicao){
    // Casas de 1 a N correspondem aos índices 0 a N-1 do vetor
    if (posicao < 1 || posicao > m->qtd_celulas) {
        return NULL; // Início (0), Fim (N+1) ou inválidas retornam NULL
    }
    return m->celulas[posicao - 1]; 
}

Jogador *obtemOcupanteMapa(Mapa *m, int posicao){
    Celula *c = obtemCelulaMapa(m, posicao);
    if (c == NULL) return NULL;
    return obtemOcupanteCelula(c);
}

void retiraJogadorMapa(Mapa *m, Jogador *j){
    int pos = obtemPosicaoJogador(j);
    // Se o jogador estiver em uma célula válida (1 a N)
    if (pos >= 1 && pos <= m->qtd_celulas) {
        Celula *c = obtemCelulaMapa(m, pos);
        if (c != NULL && obtemOcupanteCelula(c) == j) {
            defineOcupanteCelula(c, NULL);
        }
    }
}

void moveJogadorMapa(Mapa *m, Jogador *j, int posicao){
    retiraJogadorMapa(m, j);
    definePosicaoJogador(j, posicao);
    
    // Se a nova casa for uma célula válida (1 a N), marca o ocupante
    if (posicao >= 1 && posicao <= m->qtd_celulas) {
        Celula *c = obtemCelulaMapa(m, posicao);
        if (c != NULL) {
            defineOcupanteCelula(c, j);
        }
    }
}

void recuaJogadorMapa(Mapa *m, Jogador *j, int origem){
    int posicao_atual = origem - 1;
    
    while(posicao_atual > 0){
        // Verifica se a casa está livre (seja Início 0 ou célula vazia de 1 a N)
        if(posicao_atual > m->qtd_celulas || !estaOcupadaCelula(obtemCelulaMapa(m, posicao_atual))){
            // Se for casa 0 (Início), apenas move para 0
            moveJogadorMapa(m, j, posicao_atual);
            return;
        }
        // Se for célula, verifica se está ocupada
        if(posicao_atual <= m->qtd_celulas) {
            if(!estaOcupadaCelula(m->celulas[posicao_atual - 1])) {
                moveJogadorMapa(m, j, posicao_atual);
                return;
            }
        }
        posicao_atual--;
    }
    // Se tudo estiver ocupado ou chegar no limite, vai para o Início (casa 0)
    moveJogadorMapa(m, j, 0);
}

void imprimeCelulasMapa(Mapa *m){
    for(int i = 0; i < m->qtd_celulas; i++){
        if (m->celulas[i] != NULL) {
            imprimeCelula(m->celulas[i], i + 1);
        }
    }
}

void desalocaMapa(Mapa *m){
    if (m == NULL) return;
    for(int i = 0; i < m->qtd_celulas; i++){
        if(m->celulas[i] != NULL){
            desalocaCelula(m->celulas[i]);
        }
    }
    if (m->celulas != NULL) {
        free(m->celulas);
    }
    free(m);
}