#ifndef _ACAO_OURO_H_
#define _ACAO_OURO_H_

#include "jogador.h"

typedef struct Ouro Ouro;

/**
 * @brief Aloca dinamicamente uma ação do tipo ouro e guarda nela a quantidade de ouro a ser ofertada pela celula
 * @param qtd_ouro quantidade de ouro presente na acao
 * @return Ponteiro para o Ouro criado
 */
Ouro *criaOuro(int qtd_ouro);

/**
 * @brief Le da entrada padrão a quantiade de ouro disposto na celula
 * @return Ponteiro para o Ouro criado
 */
Ouro *leOuro();

/**
 * @brief Converte o dado generico para Ouro e realiza a acao
 * @param dado Ponteiro generico para o Ouro
 * @param j Jogador que parou na celula
 * @return Quantas casas o jogador deve avancar
 */
int executaOuro(void *dado, Jogador *j);

/**
 * @brief Converte o dado generico para Ouro e imprime, sem quebra de linha:
 * "OURO x" x sendo a quantidade de ouro ofertada
 * @param dado Ponteiro generico para o Ouro
 */
void imprimeOuro(void *dado);

/**
 * @brief Converte o dado generico para Ouro e libera a memoria alocada para ele
 * @param dado Ponteiro generico para o Ouro
 */
void desalocaOuro(void *dado);

#endif // _ACAO_OURO_H_
