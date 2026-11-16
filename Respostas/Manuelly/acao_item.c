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
#include "acao_item.h"

struct Item{
    int preco, bonus;
    char * nome;
};

Item *criaItem(char * nome, int preco, int bonus){
    Item * item = (Item*) calloc(1, sizeof(Item));
    item->nome = (char*) calloc(MAX_NOME_ITEM, sizeof(char));
    item->preco = preco;
    item->bonus = bonus;
    strcpy(item->nome, nome);
    return item;
}

Item *leItem(){
    int preco=0, bonus=0;
    char nome[MAX_NOME_ITEM];
    scanf(" %[^ ] %d %d", nome, &preco, &bonus);
    return criaItem(nome, preco,bonus);
}

int executaItem(void *dado, Jogador *j){
    Item * item = (Item*) dado;

    if(obtemOuroJogador(j) >= item->preco){
        adicionaOuroJogador(j, (-(item->preco)));
        adicionaForcaJogador(j, item->bonus);
    }
    
    return 0;
}

void imprimeItem(void *dado){
    Item * item = (Item*) dado;
    printf("ITEM %s (P:%d F:+%d)", item->nome,item->preco, item->bonus);
}

void desalocaItem(void *dado){
    Item * item = (Item*) dado;
    free(item->nome);
    free(item);
}