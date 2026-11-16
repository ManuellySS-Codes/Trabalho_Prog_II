#ifndef _ACAO_VOLTA_H_
#define _ACAO_VOLTA_H_

#include "jogador.h"

typedef struct Volta Volta;

/**
 * @brief Aloca dinamicamente uma ação do tipo volta e guarda nela a quantidade de voltas
 * @param tamanho_avanco_em_casas Casas puladas no volta do jogador
 * @return Ponteiro para o volta criado
 */
Volta *criaVolta(int tamanho_avanco_em_casas);

/**
 * @brief Lê da entrada padrão, na mesma linha, o nome, a força e a XP do volta (a palavra volta
 * já deve ter sido lida) e cria o volta com criavolta.
 * @return Ponteiro para o volta criado
 */
Volta *leVolta();

/**
 * @brief Converte o dado genérico para volta e realiza a acao
 * @param dado Ponteiro genérico para o volta
 * @param j ponteiro para jogador
 * @return O numero negativo de quantas casas o jogador deve voltar
 */
int executaVolta(void *dado, Jogador * j);

/**
 * @brief Converte o dado genérico para volta e imprime, sem quebra de linha:
 * "VOLTA x" x sendo o valor que o jogador deve voltar
 * @param dado Ponteiro genérico para o volta
 */
void imprimeVolta(void *dado);

/**
 * @brief Converte o dado genérico para volta e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o volta
 */
void desalocaVolta(void *dado);

#endif // _ACAO_VOLTA_H_
