#ifndef _ACAO_AVANCA_H_
#define _ACAO_AVANCA_H_

#include "jogador.h"

typedef struct Avanca Avanca;

/**
 * @brief Aloca dinamicamente uma ação do tipo Avanco e guarda nela a quantidade de avancos
 * @param n_celulas_avancadas Casas puladas no avanco do jogador
 * @return Ponteiro para o Avanco criado
 */
Avanca *criaAvanco(int n_celulas_avancadas);

/**
 * @brief Lê da entrada padrão, na mesma linha, o nome, a força e a XP do Avanco (a palavra Avanco
 * já deve ter sido lida) e cria o Avanco com criaAvanco.
 * @return Ponteiro para o Avanco criado
 */
Avanca *leAvanco();

/**
 * @brief Converte o dado genérico para Avanco e realiza a acao
 * @param dado Ponteiro genérico para o Avanco
 * @param j Jogador que parou na célula
 * @return Quantas casas o jogador deve avancar
 */
int executaAvanco(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para Avanco e imprime, sem quebra de linha:
 * "AVANCA"
 * @param dado Ponteiro genérico para o Avanco
 */
void imprimeAvanco(void *dado);

/**
 * @brief Converte o dado genérico para avanco e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o avanco
 */
void desalocaAvanco(void *dado);

#endif // _ACAO_AVANCA_H_
