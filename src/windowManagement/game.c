#include "game.h"

#include <stdlib.h>

typedef struct Resources{
    Font font; // Pra caso tenha mais coisas...
} Resources;

typedef struct GameStr{
    Resources res;
} GameStr;

Game Game_Load(){
    GameStr* g = (GameStr*)malloc(sizeof(GameStr));

    g->res.font = LoadFontEx("./assets/sprites/KiwiSoda.ttf", 40, NULL, 0);
    
    return g;
}

Font* Game_GetFont(Game game){
    GameStr* g = (GameStr*)game;
    return &g->res.font;
}

void Game_Unload(Game game){
    GameStr* g = (GameStr*)game;
    UnloadFont(g->res.font);
}