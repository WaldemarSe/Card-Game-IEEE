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

#include "carta.h"
#include "game.h"

float mySinf(float t){
    return sinf(t * 2.0f * PI) * 5.0f;
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
    
    // Imagem de placeholder
    ImageObject mainMenuBackground = Image_Init("./assets/sprites/menuBackground_p.png");
    Image_FitToScreenSize(mainMenuBackground);
    Image_SetColor(mainMenuBackground, (Color){255, 255, 255, 100});

    // Texto de placeholder
    TextObject mainMenuHeaderText = Text_Init("CompCardGame");
    Text_AddAnimation(mainMenuHeaderText, cosf, 0.0f, mySinf, 0.1f);
    Text_SetFontSize(mainMenuHeaderText, 40);
    Text_SetPosition(mainMenuHeaderText, CENTER);
    Text_SetSpacing(mainMenuHeaderText, 1.8f);

    // Botão de placeholder
    Button mainMenuStartButton = Button_Init("Start", 40, Vector2AddValue(CENTER, 40), WHITE, WHITE, RED, BLACK);

    // Tela
    while(!WindowShouldClose()){
        float deltaTime = GetFrameTime();

        BeginDrawing();
            ClearBackground(BLACK);
            Image_Draw(mainMenuBackground);

            Text_DrawAnimated(mainMenuHeaderText, deltaTime);
            Button_Draw(mainMenuStartButton);
        EndDrawing();
    }

    // Free's
    Image_FreeAll();
    Text_FreeAll();
    Button_Free(mainMenuStartButton);

    printf("\n");
    printf("|| =========================== Ending Raylib =========================== ||\n");


    printf("\n\n\n");
    printf("|| =========================== Starting Game =========================== ||\n\n");
    // 1: Cria o campo de jogo
    Carta** campo = criarCampo();
    if(campo == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create game field\n");
        return -1;
    }

    // 2: Cria algumas cartas para testar as funções do jogo
    Carta* carta1 = criarCarta(1, "Carta 1", 1, 1);
    if(carta1 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 1\n");
        return -1;
    }
    Carta* carta2 = criarCarta(2, "Carta 2", 5, 5);
    if(carta2 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 2\n");
        return -1;
    }
    Carta* carta3 = criarCarta(3, "Carta 3", 1, 1);
    if(carta3 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 3\n");
        return -1;
    }
    Carta* carta4 = criarCarta(4, "Carta 4", 10, 10);
    if(carta4 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 4\n");
        return -1;
    }

    // 3: Adiciona as cartas ao campo de jogo, verificando se a adição foi bem-sucedida
    adicionarCarta(campo, carta1, true, 0);
    adicionarCarta(campo, carta2, true, 1);
    adicionarCarta(campo, carta3, false, 2);
    adicionarCarta(campo, carta4, false, 3);
    printCampo(campo);

    // 4: Remove algumas cartas do campo de jogo, verificando se a remoção foi bem-sucedida
    removerCarta(campo, carta1, true, 0);
    removerCarta(campo, carta3, false, 2);
    printCampo(campo);

    // 5: Realiza ataques entre as cartas, verificando se os ataques foram bem-sucedidos
    atacarCarta(campo, carta2, carta4);
    printCampo(campo);
    atacarCarta(campo, carta4, carta2);
    printCampo(campo);

    // 6: Libera a memória alocada para o campo de jogo, garantindo que todos os recursos sejam corretamente desalocados
    liberarCampo(campo);
    printf("\n");
    printf("|| =========================== Ending Game ============================= ||\n\n");
    return 0;
}