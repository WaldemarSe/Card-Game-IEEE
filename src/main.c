#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#include <delimiters.h>
#include <utils.h>

#include <carta.h>

int main(){
    // Inicializa a tela
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CardGame - IEEE");
    SetTargetFPS(60);
    srand(time(NULL));

    // Pega o caminho da aplicação (para usar nos paths futuros)
    _chdir(GetApplicationDirectory());

    // Tela
    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    return 0;
}