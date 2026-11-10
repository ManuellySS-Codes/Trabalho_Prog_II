#ifndef _ACAO_VAZIO_H_
#define _ACAO_VAZIO_H_

#include "jogador.h"

typedef struct Vazio Vazio;

/**
 * @brief Aloca dinamicamente uma ação do tipo Vazio e guarda nela a quantidade de Vazios
 * @return Ponteiro para o Vazio criado
 */
Vazio *criaVazio();

/**
 * @brief Lê da entrada padrão a quantiade de Vazio disposto na celula
 * @return Ponteiro para o Vazio criado
 */
Vazio *leVazio();

/**
 * @brief Converte o dado genérico para Vazio e realiza a acao
 * @param dado Ponteiro genérico para o Vazio
 * @param j Jogador que parou na célula
 * @return Quantas casas o jogador deve avancar
 */
int executaVazio(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para Vazio e imprime, sem quebra de linha:
 * "AVANCA"
 * @param dado Ponteiro genérico para o Vazio
 */
void imprimeVazio(void *dado);

/**
 * @brief Converte o dado genérico para Vazio e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o Vazio
 */
void desalocaVazio(void *dado);

#endif // _ACAO_VAZIO_H_