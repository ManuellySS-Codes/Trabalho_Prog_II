#ifndef _ACAO_AVANCA_H_
#define _ACAO_AVANCA_H_

#include "jogador.h"

typedef struct Avanca Avanca;

/**
 * @brief Aloca dinamicamente uma ação do tipo Avanco e guarda nela a quantidade de avancos
 * @param tamanho_avanco_em_casas Casas a serem puladas no avanco do jogador
 * @return Ponteiro para o Avanco criado
 */
Avanca *criaAvanco(int tamanho_avanco_em_casas);

/**
 * @brief Lê da entrada padrão a quantidade de casas que esse avanco pula
 * @return Ponteiro para o Avanco criado
 */
Avanca *leAvanco();

/**
 * @brief Converte o dado genérico para Avanco e realiza a acao
 * @param dado Ponteiro genérico para o Avanco
 * @param j Ponteior para jogador
 * @return Quantas casas o jogador deve avancar
 */
int executaAvanco(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para Avanca e imprime, sem quebra de linha:
 * "AVANCA x" sendo x o numero de casas que o jogador ira avancar
 * @param dado Ponteiro genérico para o Avanco
 */
void imprimeAvanco(void *dado);

/**
 * @brief Converte o dado genérico para avanco e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o avanco
 */
void desalocaAvanco(void *dado);

#endif // _ACAO_AVANCA_H_
