#include "mapa.h"
#include <math.h>
#include <stdio.h>
#include "celula.h"
#include <string.h>
#include <stdlib.h>
#include "jogador.h"
#include "acao_monstro.h"
#include "dado.h"

/*typedef struct{ preciso visualizar melhor a queestao das acoes nao sei se eh o caminho certo fazer varios tads
    void*acao;
}tAcao;

typedef struct{
    tAcao acao;
    int qtd_ouro;
}tOuro;

void LeCelulas(Mapa * mapa_jogo){
    char tipo_celula[8];
    tAcao * ac = (tAcao*) calloc(1, sizeof(tAcao));
    ac->acao = NULL;
    scanf("INICIO MAPA\n");
    while(1){
        scanf(" %8s", tipo_celula);
        if(!strcmp(tipo_celula, "Vazia")){

        }else if(!strcmp(tipo_celula, "Ouro")){
            tOuro * acao_ouro = (tOuro*) ac->acao;
            scanf("%d", &acao_ouro->qtd_ouro);
            //insereCelulaMapa(mapa_jogo, acao_ouro, ExecutaAcao, Imprime, Desaloca);
        }else if(!strcmp(tipo_celula, "Item")){
            
        }else if(!strcmp(tipo_celula, "Monstro")){

        }else if(!strcmp(tipo_celula, "Avanca")){

        }else if(!strcmp(tipo_celula, "Fim")){
            break;
        }
    }
}*/ 

void DestroiJogo(Mapa*mapa_jogo, Jogador** jogadores, int qtd_jogadores){
    desalocaMapa(mapa_jogo);
    for(int i=0; i<qtd_jogadores; i++){
        desalocaJogador(jogadores[i]);
    }
}

void OrdenaJogadoresParaExibicao(Jogador ** jogadores){

}

void ImprimeRankingCompleto(Jogador ** jogadores, int qtd_jogadores){
    OrdenaJogadoresParaExibicao(jogadores); //tenho que mudar isso pois a ordem de inclusao dos jogadores tem que ser preservada  para a realizacao das jogadas e aqui ela seria alterada
     printf("=========== RANKING ===========\n");
        for(int i=0; i<qtd_jogadores; i++){
            printRankingJogador(jogadores[i], i);
        }
    printf("===============================\n");
}

void ImprimeRelatorioCompleto(Jogador ** jogadores, int qtd_jogadores, Mapa* mapa, char situacao_atual[40]){
    int monstros_derrotados=0, jogadas_totais=0, disputas=0;
        for(int i=0; i<qtd_jogadores; i++){
            jogadas_totais += obtemJogadasJogador(jogadores[i]);
            disputas += obtemDisputasVencidasJogador(jogadores[i]);
            monstros_derrotados += obtemMonstrosDerrotadosJogador(jogadores[i]);
        }

    OrdenaJogadoresParaExibicao(jogadores);
    printf("========= RELATORIO ===========\n");
    printf("- Celulas do mapa: %d\n", obtemQtdCelulasMapa(mapa));
    printf("- Jogadores: %d\n", qtd_jogadores);
    printf("- Jogadas totais: %d\n", jogadas_totais);
    printf("- Disputas: %d\n", disputas);
    printf("- Monstros derrotados: %d\n", monstros_derrotados);
    printf("Situacao: %s\n", situacao_atual);

    for(int i=0; i<qtd_jogadores; i++){
        printRelatorioJogador(jogadores[i]);
    }

    printf("===============================\n");
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

int main(){
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

    return 0;
}

