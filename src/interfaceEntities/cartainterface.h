#ifndef __CartaInterface_H__
#define __CartaInterface_H__

#include <raylib.h>
#include <stdbool.h>

#include <types.h>

typedef void* Card;

typedef enum {
    MINIMIZED = 0,
    MEDIANIZED = 1,
    MAXIMIZED = 2
} CurrentScale;

typedef enum {
    FREE = 0,
    ANIMATING = 1,
    LOCKED = 2
} CurrentState;

/**
 * @brief Inicializa uma estrutura de Card (carta).
 * @param rect Retangulo de dimensoes para a carta.
 * @param txr Textura ja' carregada na memo'ria para referenciacao na carta.
 * @return Retorna um ponteiro para a estrutura de carta criada.
 */
Card Card_Init(Rectangle rect, Texture2D txr);

Rectangle Card_GetRect(Card card);

int Card_GetId(Card card);

Card Card_GetById(int id);

bool Card_isHovered(Card card, Vector2 point);

bool Card_isGrabbed(Card card, Vector2 point, bool isDown);

bool Card_isOnAnimation(Card card);

void Card_SetRotation(Card card, float rotation);

void Card_Move(Card card, Vector2 delta);

void Card_MoveTo(Card card, Vector2 finalPoint, float duration);

void Card_Wiggle(Card card, float deltaTime);

void Card_SetScaleRatio(Card card, float scaleRatio);

void Card_SetScale(Card card, float scale, float duration);

void Card_SetRect(Card card, Rectangle rect);

void Card_Minimize(Card card, float duration);

void Card_Medianize(Card card, float duration);

void Card_Maximize(Card card, float duration);

void Card_PlayAttackAnimation(Card card, Vector2 attackPoint);

void Card_Update(Card card, float deltaTime);

void Card_UpdateLastPosition(Card card);

Vector2 Card_GetPosition(Card card);

Vector2 Card_GetLastPosition(Card card);

float Card_GetRotation(Card card);

void Card_Draw(Card card);

Texture2D Card_free(Card card);

bool compararCartas(Card card, Item id);

#endif