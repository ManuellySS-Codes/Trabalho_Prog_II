#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"
#include "dado.h"
#include "acao_avanca.h"
#include "acao_ouro.h"
#include "acao_vazio.h"
#include "acao_volta.h"
#include "jogo.h"

struct Jogo{
    Mapa*mapa;
    Jogador ** jogadores;
    int qtd_jogadores;
    char * situacao_atual;
};

Jogo* CriaJogo(){

}

Jogo* RealizaJogo(){ //mudar coisas pra se referenciarem a struct do jogo
    Mapa * mapa_jogo;
    mapa_jogo = criaMapa();
    Jogador ** jogadores;
    char operacao = '\0';
    char comando[15];
    char situacao[40];
    int qtd_jogadores=0, n_rolagens=0;

    LeCelulas(mapa_jogo);

    while(scanf(" %c", &operacao) ==1){
        if(AlguemVenceu(jogadores, qtd_jogadores, mapa_jogo) != NULL){
            sscanf(obtemNomeJogador(AlguemVenceu(jogadores, qtd_jogadores, mapa_jogo))," VENCEDOR %s", situacao);
            break;
        }else{
            strcpy("EM ANDAMENTO", situacao);
        }
        if(operacao == 'J'){
            Jogador ** jogadores = (Jogador**) realloc(jogadores, (qtd_jogadores+1) * sizeof(Jogador*));
            jogadores[qtd_jogadores] = leJogador();
            qtd_jogadores++;
        }else if(operacao == 'E'){
            scanf("%14s",comando);
            if(!strcmp(comando, "Rolagem")){
                scanf("%d", &n_rolagens);
                for(int i=0; i<n_rolagens; i++){
                    RealizaJogada(jogadores[i], mapa_jogo);
                }
            }else if(!strcmp(comando, "Ranking")){
                ImprimeRankingCompleto(jogadores, qtd_jogadores);
            }else if(!strcmp(comando, "Relatorio")){
                ImprimeRelatorioCompleto(jogadores, qtd_jogadores,mapa_jogo, situacao);
            }
        }else if(operacao == 'F'){
            DestroiJogo(mapa_jogo, jogadores, qtd_jogadores);
            break;
        }
    }
}

void DestroiJogo(Jogo * jogo){

}

/*void DestroiJogo(Mapa*mapa_jogo, Jogador** jogadores, int qtd_jogadores){ USAR SOH A STRUCT JOGO
    desalocaMapa(mapa_jogo);
    for(int i=0; i<qtd_jogadores; i++){
        desalocaJogador(jogadores[i]);
    }
}*/

void OrdenaJogadoresParaExibicao(Jogador ** jogadores){

}



Jogador* AlguemVenceu(Jogador ** jogadores, int qtd_jogadores, Mapa * mapa){
    for(int i=0; i<qtd_jogadores; i++){
        if(obtemPosicaoJogador(jogadores[i]) == obtemPosicaoFimMapa(mapa)){
            return jogadores[i]; //retorna vencedor
        }
    }
    return NULL;
}

void RealizaJogada(Jogador * jogador, Mapa * mapa){
    int avanco=0;
    incrementaJogadasJogador(jogador);
    avanco = RolaDado();
    if(avanco + obtemPosicaoJogador(jogador) < obtemPosicaoFimMapa(mapa)){ //preciso ver as coisas de acoes e disputas quando movo o jogador
        moveJogadorMapa(mapa, jogador, (avanco + obtemPosicaoJogador(jogador)));
    }else{
        definePosicaoJogador(jogador, obtemPosicaoFimMapa(mapa));
    }
    moveJogadorMapa(mapa, jogador, executaAcaoCelula(obtemCelulaMapa(mapa,obtemPosicaoJogador(jogador)), jogador)); //tenho duvida sobre o executa acao celula

}

//Impressoes

void ImprimeRankingCompleto(Jogo * jogo){
    OrdenaJogadoresParaExibicao(jogo->jogadores); //tenho que mudar isso pois a ordem de inclusao dos jogadores tem que ser preservada  para a realizacao das jogadas e aqui ela seria alterada
     printf("=========== RANKING ===========\n");
        for(int i=0; i<jogo->qtd_jogadores; i++){
            printRankingJogador(jogo->jogadores[i], i);
        }
    printf("===============================\n");
}

void ImprimeRelatorioCompleto(Jogo * jogo){
    int monstros_derrotados=0, jogadas_totais=0, disputas=0;
        for(int i=0; i<jogo->qtd_jogadores; i++){
            jogadas_totais += obtemJogadasJogador(jogo->jogadores[i]);
            disputas += obtemDisputasVencidasJogador(jogo->jogadores[i]);
            monstros_derrotados += obtemMonstrosDerrotadosJogador(jogo->jogadores[i]);
        }

    printf("========= RELATORIO ===========\n");
    printf("- Celulas do mapa: %d\n", obtemQtdCelulasMapa(jogo->mapa));
    printf("- Jogadores: %d\n", jogo->qtd_jogadores);
    printf("- Jogadas totais: %d\n", jogadas_totais);
    printf("- Disputas: %d\n", disputas);
    printf("- Monstros derrotados: %d\n", monstros_derrotados);
    printf("Situacao: %s\n", jogo->situacao_atual);

    for(int i=0; i<jogo->qtd_jogadores; i++){
        printRelatorioJogador(jogo->jogadores[i]);
    }

    printf("===============================\n");
}