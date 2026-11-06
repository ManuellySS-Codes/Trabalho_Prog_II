#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"

struct Jogador{
    char * nome;
    char * cor;
    int forca, posicao_atual, disputas_vencidas, qtd_jogadas, qtd_ouro, qtd_XP, monstros_derrotados;
};

Jogador *criaJogador(char *nome, char *cor, int forca){
    Jogador * j = (Jogador*) calloc(1, sizeof(Jogador));

    if(j == NULL){
        printf("Nao foi possivel alocar memoria para um novo jogador\n");
        exit(0);
    }

    j->nome = (char*) calloc(MAX_TAM_NOME_JOGADOR, sizeof(char)); 
    j->cor = (char*) calloc(MAX_TAM_COR_JOGADOR, sizeof(char)); 

    strcpy(j->nome, nome);
    strcpy(j->cor, cor);
    j->forca = forca;

    return j;
}

Jogador *leJogador(){
    char nome[MAX_TAM_NOME_JOGADOR];
    char cor[MAX_TAM_COR_JOGADOR];
    int forca = 0;
    scanf(" %[^\n]\n", nome);
    scanf(" %[^\n]\n", cor);
    scanf(" %d\n", &forca);

    return criaJogador(nome, cor, forca);
}

void *copiaJogador(void *d){ 
    Jogador * jogador = (Jogador*) d;
    Jogador * copia = criaJogador(jogador->nome, jogador->cor, jogador->forca);
    copia->posicao_atual = jogador->posicao_atual;
    copia->disputas_vencidas = jogador->disputas_vencidas;
    copia->qtd_jogadas = jogador->qtd_jogadas;
    copia->qtd_ouro = jogador->qtd_ouro;
    copia->qtd_XP = jogador->qtd_XP;
    copia->monstros_derrotados = jogador->monstros_derrotados;
    return copia;
}

int comparaNomeJogador(void *dado, void *nome){
    Jogador * jogador = (Jogador*) dado;
    return (!strcmp(jogador->nome, nome));
}

int comparaOrdJogador(const void *d1, const void *d2){
    Jogador **endereco_posicao1_vetor_jogadores = (Jogador **)d1;
    Jogador **endereco_posicao2_vetor_jogadores = (Jogador **)d2;
    Jogador *jogador1 = *endereco_posicao1_vetor_jogadores; 
    Jogador *jogador2 = *endereco_posicao2_vetor_jogadores;

    if(jogador1->posicao_atual > jogador2->posicao_atual){
        return -1;
    }else if(jogador1->posicao_atual < jogador2->posicao_atual){
        return 1;
    }else{
        if(jogador1->forca > jogador2->forca){
            return -1;
        }else if(jogador1->forca < jogador2->forca){
            return 1;
        }else{
            if(jogador1->qtd_XP > jogador2->qtd_XP){
                return -1;
            }else if(jogador1->qtd_XP < jogador2->qtd_XP){
                return 1;
            }else{
                return strcmp(jogador1->nome, jogador2->nome);
            }
        }
    }
}

int venceDisputaJogador(Jogador *desafiante, Jogador *ocupante){
    if(ocupante->forca > desafiante->forca){
        return 0;
    }else if(ocupante->forca < desafiante->forca){
        return 1;
    }else{
        if(ocupante->qtd_XP > desafiante->qtd_XP){
            return 0;
        }else if(ocupante->qtd_XP < desafiante->qtd_XP){
            return 1;
        }else{
            return 0;
        }
    }
}

char *obtemNomeJogador(Jogador *j){
    return j->nome;
}

int obtemPosicaoJogador(Jogador *j){
    return j->posicao_atual;
}

int obtemForcaJogador(Jogador *j){
    return j->forca;
}

int obtemXPJogador(Jogador *j){
    return j->qtd_XP;
}

int obtemOuroJogador(Jogador *j){
    return j->qtd_ouro;
}

int obtemJogadasJogador(Jogador *j){
    return j->qtd_jogadas;
}

int obtemDisputasVencidasJogador(Jogador *j){
    return j->disputas_vencidas;
}

int obtemMonstrosDerrotadosJogador(Jogador *j){
    return j->monstros_derrotados;
}

void definePosicaoJogador(Jogador *j, int posicao){ //olhar no pdf se eh isso mesmo
    j->posicao_atual = posicao;
}

void adicionaForcaJogador(Jogador *j, int forca){
    j->forca += forca;
}

void adicionaXPJogador(Jogador *j, int xp){
    j->qtd_XP += xp;
}

void adicionaOuroJogador(Jogador *j, int ouro){
    j->qtd_ouro += ouro;
}

void incrementaJogadasJogador(Jogador *j){
    j->qtd_jogadas++;
}

void incrementaDisputasVencidasJogador(Jogador *j){
    j->disputas_vencidas++;
}

void incrementaMonstrosDerrotadosJogador(Jogador *j){
    j->monstros_derrotados++;
}

void printEstadoJogador(void *dado){
    Jogador * jogador = (Jogador*) dado;
    printf("- %s: casa %d | forca %d | xp %d | ouro %d\n", jogador->nome, jogador->posicao_atual, jogador->forca, jogador->qtd_XP, jogador->qtd_ouro);
}

void printRankingJogador(Jogador *j, int colocacao){
    printf("%d. %s (%s) | casa %d | forca %d | xp %d\n", colocacao, j->nome, j->cor, j->posicao_atual, j->forca, j->qtd_XP);
}

void printRelatorioJogador(void *dado){
    Jogador * jogador = (Jogador*) dado;
    printf("- %s: jogadas %d | disputas vencidas %d | forca %d | xp %d | ouro %d\n", jogador->nome, jogador->qtd_jogadas, jogador->disputas_vencidas, jogador->forca, jogador->qtd_XP, jogador->qtd_ouro);
}

void desalocaJogador(void *dado){
    Jogador * jogador = (Jogador*) dado;
    free(jogador->nome);
    free(jogador->cor);
    free(jogador);
}