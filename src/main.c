#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#include <imageObject.h>
#include <textObject.h>
#include <button.h>

#include <delimiters.h>
#include <utils.h>

#include "screen.h"

#include "carta.h"
#include "campo.h"

extern Screen TestScreen, MenuScreen, GameScreen;
Screen gScreens[] = {};

static ScreenId current, next;
static bool changeScreen = false;

void ChangeScreen(ScreenId id){
    next = id;
    changeScreen = true;
}

int main(){
    printf("\n\n\n");
    printf("|| ========================== Starting Raylib ========================== ||\n\n");
    // Inicializa a tela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CardGame - IEEE");
    SetTargetFPS(60);
    srand(time(NULL));

    // Pega o caminho da aplicação (para usar nos paths futuros)
    _chdir(GetApplicationDirectory());
    
    Game game = Game_Load(); // (recursos, so' a fonte por enquanto)

    gScreens[0] = TestScreen;
    gScreens[1] = MenuScreen;
    gScreens[2] = GameScreen;
    // gScreens[...] == ... (caso tenham mais telas)

    current = MENUSCREEN;
    gScreens[current].Init(game);

    // Tela
    while(!WindowShouldClose()){
        float deltaTime = GetFrameTime();
        gScreens[current].Update(game, deltaTime);

        // Transição de tela
        if(changeScreen){
            gScreens[current].Unload(game);
            current = next;
            gScreens[current].Init(game);
            changeScreen = false;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            gScreens[current].Draw(game, deltaTime);
        EndDrawing();
    }

    gScreens[current].Unload(game);
    Game_Unload(game);

    CloseWindow();

    printf("\n");
    printf("|| =========================== Ending Raylib =========================== ||\n");
    return 0;
}