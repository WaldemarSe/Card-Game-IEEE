#ifndef __GAME_h__
#define __GAME_h__

#include "raylib.h"

typedef void* Game;

Game Game_Load();

// DEPOIS DE GAME_LOAD
Font* Game_GetFont(Game game);

void Game_Unload(Game game);

#endif