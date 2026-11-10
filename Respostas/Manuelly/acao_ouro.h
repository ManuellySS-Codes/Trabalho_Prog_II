#ifndef _ACAO_OURO_H_
#define _ACAO_OURO_H_

#include "jogador.h"

typedef struct Ouro Ouro;

/**
 * @brief Aloca dinamicamente uma ação do tipo Ouro e guarda nela a quantidade de Ouros
 * @param qtd_ouro quantidade de ouro presente na acao
 * @return Ponteiro para o Ouro criado
 */
Ouro *criaOuro(int qtd_ouro);

/**
 * @brief Lê da entrada padrão a quantiade de ouro disposto na celula
 * @return Ponteiro para o Ouro criado
 */
Ouro *leOuro();

/**
 * @brief Converte o dado genérico para Ouro e realiza a acao
 * @param dado Ponteiro genérico para o Ouro
 * @param j Jogador que parou na célula
 * @return Quantas casas o jogador deve avancar
 */
int executaOuro(void *dado, Jogador *j);

/**
 * @brief Converte o dado genérico para Ouro e imprime, sem quebra de linha:
 * "AVANCA"
 * @param dado Ponteiro genérico para o Ouro
 */
void imprimeOuro(void *dado);

/**
 * @brief Converte o dado genérico para Ouro e libera a memória alocada para ele
 * @param dado Ponteiro genérico para o Ouro
 */
void desalocaOuro(void *dado);

#endif // _ACAO_OURO_H_
