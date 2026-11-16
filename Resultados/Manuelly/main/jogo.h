#ifndef _JOGO_H_
#define _JOGO_H_

#include "jogador.h"

typedef struct Jogo Jogo;

/**
 * @brief Aloca memoria para o tipo Jogo
 */
Jogo * CriaJogo();

Jogo * LeCelulas(Jogo * jogo);

/**
 * @brief A funcao principal que le entradas e realiza as jogadas ateh o jogo ter um vencedor
 * @param jogo Ponteiro para o jogo
 */
Jogo * RealizaJogo(Jogo * jogo);

/**
 * @brief recebe a quantidade de rolagens do dado/jogadas que serão executadas em sequencia para cada jogador seguindo a ordem de inclusao no jogo
 * @param jogo Ponteiro para o jogo
 * @param qtd_rolagens numero de rolagens dado a partir da entrada padrao
 * @return ponteiro para o jogo
 */
Jogo * RealizaSequenciaDeRolagens(Jogo * jogo, int qtd_rolagens);

/**
 * @brief retorna o jogador que chegou ao fim do mapa
 * @param jogador ponteiro para o jogador alvo da jogada
 * @param jogo Ponteiro para o jogo
 * @param avanco_dado numero inteiro que representa o numero gerado pela rolagem do dado nessa jogada
 * @return ponteiro para o jogo
 */
Jogo * RealizaJogadas(Jogador * jogador, Jogo * jogo, int avanco_dado);

/**
 * @brief verifica a situacao atual do jogo e atualiza a string situacao atual caso haja um vencedor
 * @param jogo Ponteiro para o jogo
 * @return ponteiro para o jogo
 */
Jogo* VerificaSituacaoDoJogo(Jogo * jogo);

/**
 * @brief retorna o jogador que chegou ao fim do mapa
 * @param jogo Ponteiro para o jogo
 * @return ponteiro para o jogador vencedor
 */
Jogador* AlguemVenceu(Jogo * jogo);

/**
 * @brief Organiza o vetor de indices com base na sequencia correta para exibir os jogadores em uma ordem baseada na funcao qsort do jogo
 * @param jogo Ponteiro para o jogo
 * @param indices_ordenados vetor de indices que sera organizado e utilizado para exibir o vetor de jogadores seguindo os criterios
 */
void OrdenaJogadoresParaExibicao(Jogo * jogo, int * indices_ordenados);

/**
 * @brief Imprime ranking no formato:
 * "=========== RANKING ==========="
 * "<colocacao jogador>. <nome jogador> (<cor jogador>) | casa <casa jogador> | forca <forca jogador> | xp <xp jogador>"
 * "==============================="
 * @param jogo Ponteiro para o jogo
 */
void ImprimeRankingCompleto(Jogo * jogo);

/**
 * @brief Imprime relatorio do jogo no formato:
 * "=========== RELATORIO ==========="
 * "- Celulas do mapa: <quantidade de celulas no mapa sem conta com 0 e n+1>"
 * "- Jogadores: <quantidade de jogadores>"
 * "- Jogadas totais: <quantidade de jogadas feitas durante a partida>"
 * "- Disputas: <quantidade de disputas realizadas durante a partida>"
 * "- Monstros derrotados: <quantidade de monstros derrotados durante a partida>"
 * "- Situacao: <situacao atual do jogo>"
 * "-------------------------------"
 * "- <nome jogador>: jogadas <qtd jogadas jogador> | disputas vencidas <qtd disputas vencidas pelo jogador> | forca <qtd forca jogador> | xp <qtd xp jogador> | ouro <qtd ouro jogador>"
 * "==============================="
 * @param jogo Ponteiro para o jogo
 */
void ImprimeRelatorioCompleto(Jogo * jogo);

/**
 * @brief Imprime o estado atual do jogo e celulas no formato:
 * "=========== ESTADO ==========="
 * "[INICIO]"
 * "[x] <acao_celula> <atibutos celula>"
 * "[FIM]"
 * "-------------------------------"
 * "- <nome jogador>: casa <casa jogador>  | forca <qtd forca jogador> | xp <qtd xp jogador> | ouro <qtd ouro jogador>"
 * "- Situacao: <situacao atual do jogo>"
 * "==============================="
 * @param jogo Ponteiro para o jogo
 */
void ImprimeEstadoCompleto(Jogo * jogo);

/**
 * @brief Desaloca memoria alocada para todo o jogo
 * @param jogo Ponteiro para o jogo
 */
void DestroiJogo(Jogo * jogo);

#endif // _JOGO_H_