//essenciais
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//jogo e jogadas
#include "jogo.h"
#include "dado.h"
//gerais
#include "jogador.h"
#include "celula.h"
#include "mapa.h"
//acoes
#include "acao_monstro.h"
#include "acao_avanca.h"
#include "acao_vazio.h"
#include "acao_volta.h"
#include "acao_ouro.h"
#include "acao_item.h"

struct Jogo{
    Mapa*mapa;
    Jogador ** jogadores;
    int qtd_jogadores, indice_proximo_jogador_na_fila_jogadas;
    char * situacao_atual;
};

//--------------------------------------------------------------- ALOCACAO -----------------------------------------------------------------------------------------
Jogo* CriaJogo(){
    Jogo * jogo = (Jogo*) calloc(1, sizeof(Jogo));
    jogo->mapa = criaMapa();
    jogo->jogadores = NULL;
    jogo->situacao_atual = (char*) calloc(30, sizeof(char));
    jogo->indice_proximo_jogador_na_fila_jogadas =0;
    strcpy(jogo->situacao_atual, "EM ANDAMENTO");
    return jogo;
}

//---------------------------------------------------------------- LEITURAS -------------------------------------------------------------------------------------------
Jogo * LeCelulas(Jogo * jogo){
char tipo_celula[10];
    char lixo[20];

    scanf("%s %s", lixo, lixo);

    while(1){
        if(scanf(" %9s", tipo_celula) != 1) break;
        
        if(!strcmp(tipo_celula, "VAZIA")){
            insereCelulaMapa(jogo->mapa, leVazio(), executaVazio, imprimeVazio, desalocaVazio);
        }else if(!strcmp(tipo_celula, "OURO")){
            insereCelulaMapa(jogo->mapa, leOuro(), executaOuro, imprimeOuro, desalocaOuro);
        }else if(!strcmp(tipo_celula, "ITEM")){
            insereCelulaMapa(jogo->mapa, leItem(), executaItem, imprimeItem, desalocaItem);
        }else if(!strcmp(tipo_celula, "MONSTRO")){
            insereCelulaMapa(jogo->mapa, leMonstro(), executaMonstro, imprimeMonstro, desalocaMonstro);
        }else if(!strcmp(tipo_celula, "AVANCA")){
            insereCelulaMapa(jogo->mapa, leAvanco(), executaAvanco, imprimeAvanco, desalocaAvanco);
        }else if(!strcmp(tipo_celula, "VOLTA")){
            insereCelulaMapa(jogo->mapa, leVolta(), executaVolta, imprimeVolta, desalocaVolta);
        }else if(!strcmp(tipo_celula, "FIM")){
            scanf("%s", lixo); // Le a palavra "MAPA" correspondente ao FIM
            break;
        }
    }
    
   return jogo;
}

//---------------------------------------------------------------------- JOGADAS ------------------------------------------------------------------------------
Jogo* RealizaJogo(Jogo* jogo){
    char comando[15];
    int n_rolagens = 0;
    int flag_jogador_repetido = 0;

    jogo = LeCelulas(jogo);

    while(scanf(" %s", comando) == 1){
        if(!strcmp(comando, "J")){
            flag_jogador_repetido = 0;
            Jogador * jogador_novo = leJogador();
            for(int i = 0; i < jogo->qtd_jogadores; i++){
                if(comparaNomeJogador(jogo->jogadores[i], obtemNomeJogador(jogador_novo))){
                    //printf("NOME REPETIDO:%s\n", obtemNomeJogador(jogador_novo));
                    flag_jogador_repetido = 1;
                    break;
                }
            }
            if(flag_jogador_repetido == 0){
                jogo->jogadores = (Jogador**) realloc(jogo->jogadores, (jogo->qtd_jogadores+1) * sizeof(Jogador*));
                jogo->jogadores[jogo->qtd_jogadores] = jogador_novo;
                jogo->qtd_jogadores++;
            }else{
                desalocaJogador(jogador_novo);
            }
        }else if(!strcmp(comando, "ROLAGEM")){
            scanf("%d", &n_rolagens);
            jogo = RealizaSequenciaDeRolagens(jogo, n_rolagens);
        }else if(!strcmp(comando, "ESTADO")){
            ImprimeEstadoCompleto(jogo);
        }else if(!strcmp(comando, "RANKING")){
            ImprimeRankingCompleto(jogo);
        }else if(!strcmp(comando, "RELATORIO")){
            ImprimeRelatorioCompleto(jogo);
        }else if(!strcmp(comando, "E")){
            //O E vem acompanhado de outro comando
            char subcomando[15];
            scanf(" %s", subcomando);
            if(!strcmp(subcomando, "ROLAGEM")){
                scanf("%d", &n_rolagens);
                jogo = RealizaSequenciaDeRolagens(jogo, n_rolagens);
            }else if(!strcmp(subcomando, "ESTADO")){
                ImprimeEstadoCompleto(jogo);
            }else if(!strcmp(subcomando, "RANKING")){
                ImprimeRankingCompleto(jogo);
            }else if(!strcmp(subcomando, "RELATORIO")){
                ImprimeRelatorioCompleto(jogo);
            }
        }else if(!strcmp(comando, "F")){
            jogo = VerificaSituacaoDoJogo(jogo);
            break;
        }
        
        jogo = VerificaSituacaoDoJogo(jogo);
    }
    return jogo;
}

Jogo* VerificaSituacaoDoJogo(Jogo * jogo){
    if(AlguemVenceu(jogo) != NULL) {
        sprintf(jogo->situacao_atual, "VENCEDOR %s", obtemNomeJogador(AlguemVenceu(jogo)));
    }else{
        strcpy(jogo->situacao_atual, "EM ANDAMENTO");
    }
    return jogo;
}

Jogador* AlguemVenceu(Jogo * jogo){
    for(int i=0; i<jogo->qtd_jogadores; i++){
        if(obtemPosicaoJogador(jogo->jogadores[i]) == obtemPosicaoFimMapa(jogo->mapa)){
            return jogo->jogadores[i];
        }
    }
    return NULL;
}

Jogo * RealizaSequenciaDeRolagens(Jogo * jogo, int qtd_rolagens){
int avanco_dado = 0;

    if (jogo->qtd_jogadores <= 0 || jogo->jogadores == NULL) {
        return jogo;
    }

    for(int i=0; i<qtd_rolagens; i++){

        jogo = VerificaSituacaoDoJogo(jogo);

        if(strcmp(jogo->situacao_atual, "EM ANDAMENTO") != 0){
            break;
        }

        if(jogo->indice_proximo_jogador_na_fila_jogadas >= jogo->qtd_jogadores){
            jogo->indice_proximo_jogador_na_fila_jogadas = 0;
        }
        
        avanco_dado = RolaDado();
        jogo = RealizaJogadas(jogo->jogadores[jogo->indice_proximo_jogador_na_fila_jogadas], jogo, avanco_dado); 

        jogo->indice_proximo_jogador_na_fila_jogadas++;

    }
    return jogo;
}

Jogo * RealizaJogadas(Jogador * jogador, Jogo * jogo, int avanco_dado){
    int avanco_resultante_execucao_acao = 0, posicao_cobicada = 0, posicao_original = 0;
    posicao_original = obtemPosicaoJogador(jogador);
    posicao_cobicada = avanco_dado + posicao_original;
    int fim_mapa = obtemPosicaoFimMapa(jogo->mapa);

    incrementaJogadasJogador(jogador);

    if(posicao_cobicada >= fim_mapa){
        moveJogadorMapa(jogo->mapa, jogador, fim_mapa);
        return jogo;
    }

    Celula * celula_cobicada = obtemCelulaMapa(jogo->mapa, posicao_cobicada);
    Jogador * desafiante = jogador;

if(estaOcupadaCelula(celula_cobicada)){
        Jogador * ocupante = obtemOcupanteCelula(celula_cobicada);
        //printf("\nDESAFIANTE: %s OCUPANTE:%s\n", obtemNomeJogador(desafiante), obtemNomeJogador(ocupante));
        //printEstadoJogador(desafiante);
        //printEstadoJogador(ocupante);
        if(venceDisputaJogador(desafiante, ocupante)){
            //printf("VENCEDOR: %s\n", obtemNomeJogador(desafiante));
            retiraJogadorMapa(jogo->mapa, desafiante); //retirar o jogador antes de recuar o ocupante para que o ocupante nao tente recuar e veja a casa antiga como ocupada ainda (antes do movimento do jogador ser efetivo)
            recuaJogadorMapa(jogo->mapa, ocupante, posicao_cobicada);
            moveJogadorMapa(jogo->mapa, desafiante, posicao_cobicada);
            incrementaDisputasVencidasJogador(desafiante);
            avanco_resultante_execucao_acao = executaAcaoCelula(celula_cobicada, desafiante); 
        }else{
            //printf("VENCEDOR: %s\n", obtemNomeJogador(ocupante));
            incrementaDisputasVencidasJogador(ocupante);
            retiraJogadorMapa(jogo->mapa, desafiante); // Libera apenas a casa de origem do desafiante
            recuaJogadorMapa(jogo->mapa, desafiante, posicao_cobicada); // Recua a partir da casa cobiçada
            return jogo;
        }
    }else{
        moveJogadorMapa(jogo->mapa, jogador, posicao_cobicada);
        avanco_resultante_execucao_acao = executaAcaoCelula(celula_cobicada, jogador); 
    }

    if(avanco_resultante_execucao_acao == RECUO_CELULA){
        recuaJogadorMapa(jogo->mapa, jogador, obtemPosicaoJogador(jogador));
    }else if(avanco_resultante_execucao_acao != 0){
        int posicao_final_pos_acao = posicao_cobicada + avanco_resultante_execucao_acao;
        
        if(posicao_final_pos_acao >= fim_mapa){
            moveJogadorMapa(jogo->mapa, jogador, fim_mapa);
        }else if(posicao_final_pos_acao <= 0){
            moveJogadorMapa(jogo->mapa, jogador, 0);
        }else{
            posicao_cobicada = posicao_final_pos_acao;
            Celula * celula_pos_acao = obtemCelulaMapa(jogo->mapa, posicao_cobicada);
            
    
            if(estaOcupadaCelula(celula_pos_acao)){
                Jogador * ocupante = obtemOcupanteCelula(celula_pos_acao);
                //printf("\nDESAFIANTE: %s OCUPANTE:%s\n", obtemNomeJogador(desafiante), obtemNomeJogador(ocupante));
                //printEstadoJogador(desafiante);
                //printEstadoJogador(ocupante);

                if(venceDisputaJogador(desafiante, ocupante)){
                    //printf("VENCEDOR: %s\n", obtemNomeJogador(desafiante));
                    retiraJogadorMapa(jogo->mapa, desafiante);
                    recuaJogadorMapa(jogo->mapa, ocupante, posicao_cobicada);
                    moveJogadorMapa(jogo->mapa, desafiante, posicao_cobicada);
                    incrementaDisputasVencidasJogador(desafiante);
                }else{
                    //printf("VENCEDOR: %s\n", obtemNomeJogador(ocupante));
                    incrementaDisputasVencidasJogador(ocupante);
                    retiraJogadorMapa(jogo->mapa, desafiante); // Libera apenas a casa de origem do desafiante
                    recuaJogadorMapa(jogo->mapa, desafiante, posicao_cobicada); // Recua a partir da casa cobiçada
                    return jogo;
                }

            }else{
                moveJogadorMapa(jogo->mapa, desafiante, posicao_cobicada);
            }
        } 
    }
    return jogo;
}

//---------------------------------------------------------------------- IMPRESSOES --------------------------------------------------------------------------

void OrdenaJogadoresParaExibicao(Jogo * jogo, int * indices_ordenados){
    int aux=0;
    for(int i = 0; i < jogo->qtd_jogadores; i++){
        indices_ordenados[i] = i;
    }
    for(int i = 0; i < jogo->qtd_jogadores - 1; i++){
        for(int j = 0; j < jogo->qtd_jogadores - i - 1; j++){
            if(comparaOrdJogador(&jogo->jogadores[indices_ordenados[j]], &jogo->jogadores[indices_ordenados[j+1]]) > 0){
                aux = indices_ordenados[j];
                indices_ordenados[j] = indices_ordenados[j+1];
                indices_ordenados[j+1] = aux;
            }
        }
    }
}   

void ImprimeRankingCompleto(Jogo * jogo){
    int indices_ordenados[jogo->qtd_jogadores];
    

    OrdenaJogadoresParaExibicao(jogo, indices_ordenados); 

    printf("=========== RANKING ===========\n");

    for(int i = 0; i < jogo->qtd_jogadores; i++){
        printRankingJogador(jogo->jogadores[indices_ordenados[i]], i+1); 
    }

    printf("===============================\n");
}

void ImprimeRelatorioCompleto(Jogo * jogo){
    int monstros_derrotados = 0, jogadas_totais = 0, disputas = 0;
    
    for(int i = 0; i < jogo->qtd_jogadores; i++){
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
    printf("- Situacao: %s\n", jogo->situacao_atual);


    printf("-------------------------------\n");

    for(int i =0; i < jogo->qtd_jogadores; i++){
        printRelatorioJogador(jogo->jogadores[i]);
    }

    printf("===============================\n");
}

void ImprimeEstadoCompleto(Jogo * jogo){
    int printados=0;
    printf("=========== ESTADO ============\n");

    printf("[INICIO]");
    for(int i=0; i<jogo->qtd_jogadores; i++){
        if(obtemPosicaoJogador(jogo->jogadores[i]) ==0){
            if(printados == 0){
                printf(" <- %s", obtemNomeJogador(jogo->jogadores[i]));
                printados++;
            }else{
                printf(", %s", obtemNomeJogador(jogo->jogadores[i]));
            }
        }
    }
    printf("\n");

    for(int i=1; i<=obtemQtdCelulasMapa(jogo->mapa); i++){
        imprimeCelula(obtemCelulaMapa(jogo->mapa, i), i);
    }
    printf("[FIM]");
    printados=0;
    for(int i=0; i<jogo->qtd_jogadores; i++){
        if(obtemPosicaoJogador(jogo->jogadores[i]) == obtemPosicaoFimMapa(jogo->mapa)){
            if(printados == 0){
                printf(" <- %s", obtemNomeJogador(jogo->jogadores[i]));
                printados++;
            }else{
                printf(", %s", obtemNomeJogador(jogo->jogadores[i]));
            }
        }
    }
    printf("\n");

    printf("-------------------------------\n");


    for(int i =0; i < jogo->qtd_jogadores; i++){
        printEstadoJogador(jogo->jogadores[i]);
    }

    printf("- Situacao: %s\n", jogo->situacao_atual);

    printf("===============================\n");

}

//---------------------------------------------------------------- DESALOCACAO ----------------------------------------------------------------------------------------------------
void DestroiJogo(Jogo * jogo){
    free(jogo->situacao_atual);
    for(int i=0; i<jogo->qtd_jogadores; i++){
        desalocaJogador(jogo->jogadores[i]);
    }
    free(jogo->jogadores);
    desalocaMapa(jogo->mapa);
    free(jogo);
}