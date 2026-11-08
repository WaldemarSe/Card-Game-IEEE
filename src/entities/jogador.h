#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include <stdbool.h>

#include "../libraries/data_structures/lista.h"

/** JOGADOR:  
 * @file jogador.h
 * @authors Waldemar Serafim (waldemar.serafim.neto@uel.br)
 * @brief Classe que representa um jogador da partida, seja o player ou o computador.
 * @date 2023-04-01
 * @struct Jogador: contém a vida (inteiro), mão e baralho do jogador, representados como listas. 
 * 
 * Essa classe é responsável por gerenciar os dados do jogador, como vida, mão e baralho. Apresenta 
 * funções para criar, carregar baralho, comprar cartas e liberar memória. O baralho é carregado a 
 * partir de um arquivo JSON, e a mão e o baralho são representados como listas.
 * 
 * Manter o cabeçalho bem documentado para o entendimento dos demais. 
 * Os métodos e atributos podem ser ajustados conforme a demanda do projeto, 
 * não sendo necessário implementar apenas o que está no diagrama de classes, 
 * visto que novos métodos e talvez atributos serão necessários durante o decorrer do projeto.
*/
  

typedef void* Jogador; // Ponteiro para o Jogador


/* =============================================== FUNÇÕES PRINCIPAIS ================================================ */

/** criarJogador
 * @brief Cria um jogador com a vida especificada, inicializando sua mão e baralho como listas vazias.
 * 
 * @param vida          Vida do jogador.
 * 
 * @return Ponteiro para o jogador criado.
 */
Jogador criarJogador(int vida);


/** carregarBaralho
 * @brief Carrega o baralho do jogador especificado a partir de um arquivo.
 * 
 * @param jogador        Ponteiro para o jogador.
 * @param playerFlag     Flag indicando se é o jogador humano (true) ou o computador (false).
 * @param caminhoArquivo Caminho para o arquivo contendo as cartas do baralho.
 * 
 * @return Booleano indicando se o baralho foi carregado com sucesso (true) ou não (false).
 */
bool carregarBaralho(Jogador jogador, bool playerFlag, const char* caminhoArquivo);


/** comprarCarta
 * @brief Compra uma carta do baralho do jogador e a adiciona à sua mão.
 * 
 * @param jogador       Ponteiro para o jogador.
 * 
 * @return Booleano indicando se a carta foi comprada com sucesso (true) ou não (false).
 */
bool comprarCarta(Jogador jogador);


/** liberarJogador
 * @brief Libera a memória alocada para o jogador especificado.
 * 
 * @param jogador       Ponteiro para o jogador.
 */
void liberarJogador(Jogador jogador);

/* =============================================== FUNÇÕES SECUNDÁRIAS (SETTERS/GETTERS) ================================================ */

/** setVidaJogador
 * @brief Define um novo valor de vida ao jogador especificado.
 * 
 * @param jogador       Ponteiro para o jogador.
 * @param vida          Vida atual do jogador.
 */
void setVidaJogador(Jogador jogador, int vida);


/** getVidaJogador
 * @brief Obtém a vida do jogador especificado.
 * 
 * @param jogador       Ponteiro para o jogador.
 * 
 * @return Vida atual do jogador.
 */
int getVidaJogador(Jogador jogador);


/** getMaoJogador
 * @brief Obtém a mão do jogador especificado.
 * 
 * @param jogador       Ponteiro para o jogador.
 * 
 * @return Ponteiro para a Lista contendo as cartas da mão do jogador.
 */
Lista getMaoJogador(Jogador jogador);


/** getBaralhoJogador
 * @brief Obtém o baralho do jogador especificado.
 * 
 * @param jogador       Ponteiro para o jogador.
 * 
 * @return Ponteiro para a Lista contendo as cartas do baralho do jogador.
 */
Lista getBaralhoJogador(Jogador jogador);

/** embaralharBaralho
 * @brief Embaralha o baralho do jogador especificado.
 * 
 * @param jogador       Ponteiro para o jogador.
 * 
 */
void embaralharBaralho(Jogador jogador);

void printBaralho(Jogador jogador);

#endif