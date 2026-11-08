#ifndef _CARD_h_
#define _CARD_h_

/** CARTA:
 * @file carta.h
 * @authors Waldemar Serafim (waldemar.serafim.neto@uel.br), Bruna Yokoshiro (bruna.yokoshiro@uel.br)
 * @brief Classe que representa uma carta do jogo.
 * @date 2023-04-01
 * @struct Carta: contém os atributos da carta, como ID, nome, ataque, vida, sprite e flag do jogador.
 *
 * 
 * Essa classe será responsável por gerenciar os dados da carta, que será a estrutura principal do jogo. 
 * Apresenta funções para criar, acessar e modificar os atributos da carta. O sprite é representado como 
 * uma string contendo o caminho para a imagem da carta.
 * 
 * Manter o cabeçalho bem documentado para o entendimento dos demais. 
 * Os métodos e atributos podem ser ajustados conforme a demanda do projeto, 
 * não sendo necessário implementar apenas o que está no diagrama de classes, 
 * visto que novos métodos e talvez atributos serão necessários durante o decorrer do projeto.
*/

typedef void* Carta; // Ponteiro para o Card

Carta criarCarta(const char* nome, int atk, int vida, const char* spritePath, bool playerFlag);

int getID(Carta c);

const char* getNome(Carta c);

int getAtk(Carta c);

int getVida(Carta c);

int getPosX(Carta c);

int getPosY(Carta c);

const char* getSpritePath(Carta c);

bool getPlayerFlag(Carta c);

void setAtk(Carta c, int atk);

void setVida(Carta c, int vida);

void setPos(Carta c, int pos[2]);

void setPlayerFlag(Carta c, bool playerFlag);

void killCarta(Carta c);

// AUXILIAR
void printCarta(Carta c);

#endif