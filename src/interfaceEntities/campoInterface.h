#ifndef __CampoInterface_H__
#define __CampoInterface_H__

#include <raylib.h>
#include <stdbool.h>

#include <lista.h>
#include <types.h>

typedef void* Field;

typedef enum CurrentFieldScale{
    MINIMIZEDFIELD = 0,
    MEDIANIZEDFIELD = 1,
    MAXIMIZEDFIELD = 2
} CurrentFieldScale;

/**
 * @brief Inicializa uma estrutura de Field (campo).
 * @param rect Retangulo de dimensoes para o campo.
 * @param txr Textura ja' carregada na memo'ria para o background do campo (opcional).
 * @return Retorna um ponteiro para a estrutura de campo.
 */
Field Field_Init(Rectangle rect, Texture2D txr, int maxItems);

Rectangle Field_GetRect(Field field);

int Field_GetId(Field field);

bool Field_isHovered(Field field, Vector2 point);

void Field_SetRotation(Field field, float rotation);

void Field_Move(Field field, Vector2 delta);

void Field_MoveTo(Field field, Vector2 finalPoint, float duration);

void Field_SetScaleRatio(Field field, float scaleRatio);

void Field_SetScale(Field field, float scale, float duration);

void Field_MinimizeContent(Field field, float duration);

void Field_MedianizeContent(Field field, float duration);

void Field_MaximizeContent(Field field, float duration);

void Field_Update(Field field, float deltaTime);

void Field_UpdateLastPosition(Field field);

typedef Item (*getItemFuncMatrix) (Item item, int x, int y);

void Field_AssignMatrixObject(Field field, Item object, getItemFuncMatrix objSearchFunc, int sizeX, int sizeY);

Vector2 Field_GetPosition(Field field);

Vector2 Field_GetLastPosition(Field field);

float Field_GetRotation(Field field);

void Field_Draw(Field field);

void Field_DrawFromMatrixObject(Field field);

Lista Field_free(Field field);

#endif