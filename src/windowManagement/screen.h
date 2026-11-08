#ifndef __SCREEN_h__
#define __SCREEN_h__

#include "game.h"

typedef enum { MENUSCREEN, GAMESCREEN, COUNTSCREEN } ScreenId;

typedef struct {
    void (*Init)(Game game);
    void (*Update)(Game game, float deltaTime);
    void (*Draw)(Game game, float deltaTime);
    void (*Unload)(Game game);
} Screen;

extern Screen gScreens[COUNTSCREEN];
void ChangeScreen(ScreenId id);

#endif