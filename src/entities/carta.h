#ifndef _CARD_h_
#define _CARD_h_

#include "../libraries/data_structures/lista.h"

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

Carta criarCarta(int id, char* nome, int atk, int vida, char* sprite, bool playerFlag);

void printCarta(Carta c, void* extra);

void killCarta(Item item, void* extra);

int getAtk(Carta c);

void setAtk(Carta c, int atk);

int getVida(Carta c);

void setVida(Carta c, int vida);

int getID(Carta c);

char* getNome(Carta c);

char* getSprite(Carta c);

bool getPlayerFlag(Carta c);

int getPosX(Carta c);

int getPosY(Carta c);

void setPos(Carta c, int pos[2]);

bool getPlayerFlag(Carta c);

void setPlayerFlag(Carta c, bool playerFlag);


/* 

Card Card_Init(Rectangle rect, Texture2D txr);

Rectangle Card_GetRect(Card card);

int Card_GetId(Card card);

bool Card_isHovered(Card card, Vector2 point);

bool Card_isGrabbed(Card card, bool isDown);

void Card_SetRotation(Card card, float rotation);

void Card_Move(Card card, Vector2 delta);

void Card_MoveTo(Card card, Vector2 finalPoint, float duration);

void Card_Wiggle(Card card, float deltaTime);

void Card_SetScaleRatio(Card card, float scaleRatio);

void Card_SetScale(Card card, float scale, float duration);

void Card_Minimize(Card card, float duration);

void Card_Medianize(Card card, float duration);

void Card_Maximize(Card card, float duration);

void Card_Update(Card card, float deltaTime);

void Card_UpdateLastPosition(Card card);

Vector2 Card_GetPosition(Card card);

Vector2 Card_GetLastPosition(Card card);

float Card_GetRotation(Card card);

void Card_Draw(Card card);

Texture2D Card_free(Card card);

 */

#endif