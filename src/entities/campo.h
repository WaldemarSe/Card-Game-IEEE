#ifndef _CAMPO_H_
#define _CAMPO_H_

/** CAMPO: Campo/Jogo
 * @file campo.h
 * @authors André Felipe Ijiri Ribeiro(andre.ijiri.ribeiro@gmail.com) e Bruna Yokoshiro()
 * @brief Classe que representa o jogo ou o campo de jogo.
 * @date 2026-09-01
 * 
 * Para fins de simplificação, a classe Jogo (ou Campo) será responsável por rodar toda a interface 
 * bem como os dados essenciais para a partida (jogadores, cartas, o campo propriamente dito, etc.). 
 * Essa classe terá forte relação com o Raylib, que irá integrar visualmente os elementos do jogo. 
 * Para que ela funcione, é essencial que as classes de Carta e Jogadores já estejam funcionando.
 * 
 * Manter o cabeçalho bem documentado para o entendimento dos demais. 
 * Os métodos e atributos podem ser ajustados conforme a demanda do projeto, 
 * não sendo necessário implementar apenas o que está no diagrama de classes, 
 * visto que novos métodos e talvez atributos serão necessários durante o decorrer do projeto.
*/



#include <stdbool.h>

#include "carta.h"
#include "jogador.h"

typedef void* Campo;

/* =============================================== FUNÇÕES PRINCIPAIS ================================================ */
/** criarCampo
 * @brief Cria o campo de jogo, inicializando os elementos e estruturas essenciais para a partida.
 * @return Retorna um ponteiro para o campo criado.
 */
Campo criarCampo();

/** adicionarCarta
 * @brief Adiciona uma carta ao campo de jogo, atualizando as estruturas e elementos visuais conforme necessário.
 * 
 * @param campo         Ponteiro para o campo onde a carta será adicionada.
 * @param carta         Ponteiro para a carta a ser adicionada.
 * @param pos           Posição onde a carta deve ser adicionada.
 * 
 * @return Retorna TRUE se a carta foi adicionada com sucesso. FALSE caso contrário.
 */
bool adicionarCarta(Campo campo, Carta carta, int pos);

/** removerCarta
 * @brief Remove uma carta do campo de jogo, atualizando as estruturas e elementos visuais conforme necessário.
 * NOTA: A carta é removida do campo, a devida liberação da carta deve ser feita externamente.
 * 
 * @param campo         Ponteiro para o campo de onde a carta será removida.
 * @param carta         Ponteiro para a carta a ser removida.
 * 
 * @return Retorna TRUE se a carta foi removida com sucesso. FALSE caso contrário.
 */
bool removerCarta(Campo campo, Carta carta);

/** atacarCartas
 * @brief Realiza um ataque de uma carta atacante contra uma carta alvo, aplicando as regras do jogo.
 * 
 * @param campo         Ponteiro para o campo de jogo.
 * @param ataqueFlag    Flag que indica se o ataque é do jogador ou do oponente.
 * @param jogador       Ponteiro para o jogador que está atacando.
 * 
 * @return Retorna TRUE se o ataque foi realizado com sucesso. FALSE se houve algum erro (ex: campo nulo).
 */
bool atacarCartas(Campo campo, bool ataqueFlag, Jogador jogador);

/** moverCartas
 * @brief Move todas as cartas do campo de jogo uma posição para frente, atualizando as estruturas e elementos visuais conforme necessário.
 * 
 * @param campo Ponteiro para o campo de jogo.
 */
void moverCartas(Campo campo);

/** liberarCampo
 * @brief Libera a memória alocada para o campo de jogo, garantindo que todos os recursos sejam corretamente desalocados.
 * @note Será utilizado a ferramenta de Valgrind para verificar se não há vazamentos de memória.
 * 
 * @param campo Ponteiro para o campo a ser liberado.
 * 
 * @return Retorna uma lista de cartas que pertenciam ao campo destruído.
 */
Lista liberarCampo(Campo campo);
/* =================================================================================================================== */

/* =============================================== FUNÇÕES SECUNDÁRIAS =============================================== */
/** printCampo
 * @brief Imprime o estado atual do campo de jogo, mostrando as cartas presentes e suas posições.
 * 
 * @param campo Ponteiro para o campo a ser impresso.
 */
void printCampo(Campo campo);

/** playerAtaque
 * @brief Realiza um ataque de uma carta contra o alvo, aplicando as regras do jogo para o jogador.
 * 
 * @param campo     Ponteiro para o campo de jogo.
 * 
 * @return Retorna TRUE se o ataque foi realizado com sucesso. FALSE se houve algum erro (ex: campo nulo).
 */
bool playerAtaque(Campo campo);

/** oponenteAtaque
 * @brief Realiza um ataque de uma carta atacante contra uma carta alvo, aplicando as regras do jogo para o oponente.
 * 
 * @param campo     Ponteiro para o campo de jogo.
 * @param jogador   Ponteiro para o jogador que está atacando.
 * 
 * @return Retorna TRUE se o ataque foi realizado com sucesso. FALSE se houve algum erro (ex: campo nulo).
 */
bool oponenteAtaque(Campo campo, Jogador jogador);
/* =================================================================================================================== */

#endif