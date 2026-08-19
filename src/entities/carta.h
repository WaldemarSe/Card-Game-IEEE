#ifndef _CARD_h_
#define _CARD_h_

/*
    Um exemplo de como ficariam os arquivos .h
*/

typedef void* Carta; // Ponteiro para o Card

int getAtk(Carta c);

void setAtk(Carta c, int atk);

int getVida(Carta c);

void setVida(Carta c, int vida);

void killCarta(Carta c);

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