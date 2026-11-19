#ifndef _ACAO_ITEM_H_
#define _ACAO_ITEM_H_

#include "jogador.h"

#define MAX_NOME_ITEM 21

typedef struct Item Item;

/**
 * @brief Aloca dinamicamente uma ação do tipo item e guarda nela os dados do item
 * @param nome nome do item a ser alocado
 * @param preco preco do item a ser alocado
 * @param bonus bonus que o item a ser alocado fornece para o jogador acrescentando em sua forca
 * @return Ponteiro para o Item criado
 */
Item *criaItem(char * nome, int preco, int bonus);

/**
 * @brief Le da entrada padrao o item no formato <nome> <preco> <bonus>
 * @return Ponteiro para o Item criado
 */
Item *leItem();

/**
 * @brief Converte o dado generico para Item e realiza a acao
 * @param dado Ponteiro generico para o Item
 * @param j Jogador que parou na célula
 * @return Quantas casas o jogador deve avancar
 */
int executaItem(void *dado, Jogador *j);

/**
 * @brief Converte o dado generico para Item e imprime, sem quebra de linha:
 * "Item <nome> (p: <preco> f +<bonus>)"
 * @param dado Ponteiro generico para o Item
 */
void imprimeItem(void *dado);

/**
 * @brief Converte o dado generico para Item e libera a memoria alocada para ele
 * @param dado Ponteiro generico para o Item
 */
void desalocaItem(void *dado);

#endif // _ACAO_ITEM_H_
