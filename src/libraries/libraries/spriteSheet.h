#ifndef _SPRITESHEET_h_
#define _SPRITESHEET_h_

#include <raylib.h>

typedef void* SpriteSheet;

typedef void* AnimatedSpriteSheetInstance;

SpriteSheet SpriteSheet_Init(const char* filename, Vector2 delta, Vector2 size, Rectangle dest);

AnimatedSpriteSheetInstance SpriteSheet_CreateAnimatedInstance(SpriteSheet spriteSheet, const char* name, Rectangle destination);

// SpriteSheet SpriteSheet_Copy(SpriteSheet spriteSheet);

void SpriteSheet_AddIndex(SpriteSheet spriteSheet, const char* name, int row, int amountOfFrames, float speed);

void SpriteSheet_AddStaticIndex(SpriteSheet spriteSheet, const char* name, int row, int column);

void SpriteSheet_SetFrame(SpriteSheet spriteSheet, const char* name);

Vector2 SpriteSheet_GetFramePosition(SpriteSheet spriteSheet, const char* name);

void SpriteSheet_SetDestination(SpriteSheet spriteSheet, Rectangle destination);

Rectangle SpriteSheet_GetDestination(SpriteSheet spriteSheet);

Rectangle SpriteSheet_GetInstanceRec(AnimatedSpriteSheetInstance animatedSprite);

void SpriteSheet_UpdateAnimation(SpriteSheet spriteSheet, float deltaTime);

void SpriteSheet_UpdateInstance(SpriteSheet spriteSheet, AnimatedSpriteSheetInstance animatedSprite, float deltaTime);

void SpriteSheet_DrawImage(SpriteSheet spriteSheet);

void SpriteSheet_DrawIndex(SpriteSheet spriteSheet, Vector2 coords);

void SpriteSheet_DrawInstance(SpriteSheet spriteSheet, AnimatedSpriteSheetInstance animatedSprite);

void SpriteSheet_Free(SpriteSheet spriteSheet);

void SpriteSheet_FreeAnimatedInstance(AnimatedSpriteSheetInstance animatedSprite);

void SpriteSheet_FreeAll();

#endif