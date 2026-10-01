#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#include <delimiters.h>
#include <utils.h>

#include "carta.h"
#include "game.h"

int main(){
    printf("\n\n\n");
    printf("|| ========================== Starting Raylib ========================== ||\n\n");
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
    printf("\n");
    printf("|| =========================== Ending Raylib =========================== ||\n");


    printf("\n\n\n");
    printf("|| =========================== Starting Game =========================== ||\n\n");
    // 1: Cria as estruturas de dados essenciais para o jogo, incluindo o campo de jogo e o jogador
    Carta** campo = criarCampo();
    if(campo == NULL){
        printf("[ERROR]: main.c: main()\n");
        printf("Failed to create game field\n");
        return -1;
    }
    Jogador* jogador = criarJogador(10);
    if(jogador == NULL){
        printf("[ERROR]: main.c: main()\n");
        printf("Failed to create player\n");
        return -1;
    }

    // 2: Cria algumas cartas para testar as funções do jogo
    Carta* carta1 = criarCarta(1, "Carta 1", 1, 1, true);
    if(carta1 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 1\n");
        return -1;
    }
    Carta* carta2 = criarCarta(2, "Carta 2", 5, 5, true);
    if(carta2 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 2\n");
        return -1;
    }
    Carta* carta3 = criarCarta(3, "Carta 3", 1, 1, false);
    if(carta3 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 3\n");
        return -1;
    }
    Carta* carta4 = criarCarta(4, "Carta 4", 10, 10, false);
    if(carta4 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 4\n");
        return -1;
    }
    Carta* carta5 = criarCarta(5, "Carta 5", 15, 15, false);
    if(carta5 == NULL){
        printf("[ERROR]\n");
        printf("in main.c: main()\n");
        printf("Failed to create card 5\n");
        return -1;
    }

    // 3: ADIÇÃO E REMOÇÃO DE CARTAS
    printf("\nTESTING ADDING AND REMOVING CARDS\n");
    adicionarCarta(campo, carta5, 0);
    printCampo(campo);
    removerCarta(campo, carta5);
    printCampo(campo);

    // 4: ADIÇÃO DE CARTAS EM POSIÇÕES DIFERENTES
    printf("\nTESTING ADDING CARDS IN DIFFERENT POSITIONS\n");
    adicionarCarta(campo, carta1, 0);
    adicionarCarta(campo, carta2, 1);
    adicionarCarta(campo, carta3, 1);
    adicionarCarta(campo, carta4, 2);
    printCampo(campo);

    // 5: MOVIMENTAÇÃO DE CARTAS DO OPONENTE
    printf("\nTESTING MOVING OPPONENT CARDS\n");
    printCampo(campo);
    moverCartas(campo);
    printCampo(campo);

    // 6: Realiza ataques entre as cartas, verificando se os ataques foram bem-sucedidos
    printf("\nTESTING CARD ATTACKS\n");
    printCampo(campo);
    atacarCartas(campo, false, jogador);
    atacarCartas(campo, true, jogador);
    printCampo(campo);
    atacarCartas(campo, false, jogador);
    printCampo(campo);

    // 7: Libera a memória alocada para o campo de jogo, garantindo que todos os recursos sejam corretamente desalocados
    printf("\nTESTING FREEING GAME FIELD MEMORY\n");
    printCampo(campo);
    liberarCampo(campo);

    printf("\n");
    printf("|| =========================== Ending Game ============================= ||\n\n");
    return 0;
}