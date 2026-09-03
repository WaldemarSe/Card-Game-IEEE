#include <stdio.h>
#include <stdlib.h>
#include "game.h"



/* =============================================== ESTRUTURAS DE DADOS =============================================== */
/** CAMPO: Estrutura de dados para representar o campo de jogo.
 * 
 * @param cartas     Array de ponteiros para cartas no campo.
 * @param tamanho    Tamanho atual do campo.
 * @param capacidade Capacidade máxima do campo.
 */
typedef struct Campo{
    Carta* cartas;
    int tamanho;
    int capacidade;
} Campo;
/* =================================================================================================================== */



#define ROWS 3
#define COLS 4
/* =============================================== FUNÇÕES PRINCIPAIS ================================================ */
void* criarCampo(){
    int** campo = (int**)malloc(ROWS * sizeof(int*));
    if(campo == NULL){
        printf("[ERROR]\n");
        printf("in game.c: criarCampo()\n");
        printf("First game field memory allocation failed\n");
        return NULL;
    }

    for(int i = 0; i < ROWS; i++){
        campo[i] = (int*)malloc(COLS * sizeof(int));
        if(campo[i] == NULL){
            printf("[ERROR]\n");
            printf("in game.c: criarCampo()\n");
            printf("Second game field memory allocation failed\n");
            return NULL;
        }

        for(int j = 0; j < COLS; j++) {campo[i][j] = 0;}
    }

    return (void*)campo;
}

bool adicionarCarta(Carta* carta, int pos){
    if(carta == NULL){
        printf("[ERROR]\n");
        printf("in game.c: adicionarCarta()\n");
        printf("Card is NULL, cannot add to field\n");
        return false;
    }
    if(pos < 0 || pos >= ROWS * COLS){
        printf("[ERROR]\n");
        printf("in game.c: adicionarCarta()\n");
        printf("Position %d is out of bounds for the field\n", pos);
        return false;
    }

    // Lógica para adicionar a carta ao campo na posição especificada
    // ...

    return true;
}

bool removerCarta(Carta* carta, int pos){
    if(carta == NULL){
        printf("[ERROR]\n");
        printf("in game.c: removerCarta()\n");
        printf("Card is NULL, cannot remove from field\n");
        return false;
    }
    if(pos < 0 || pos >= ROWS * COLS){
        printf("[ERROR]\n");
        printf("in game.c: removerCarta()\n");
        printf("Position %d is out of bounds for the field\n", pos);
        return false;
    }

    // Lógica para remover a carta do campo na posição especificada
    // ...

    return true;
}

int atacarCarta(Carta* atacante, Carta* alvo){
    if(atacante == NULL){
        printf("[ERROR]\n");
        printf("in game.c: atacarCarta()\n");
        printf("Attacker card is NULL, cannot perform attack\n");
        return -1;
    }
    if(alvo == NULL){
        printf("[ERROR]\n");
        printf("in game.c: atacarCarta()\n");
        printf("Target card is NULL, cannot perform attack\n");
        return -1;
    }

    // Lógica para realizar o ataque da carta atacante contra a carta alvo
    // ...

    // Retorna resultado do ataque (ex: dano causado)
    return 0;
}

void liberarCampo(void* campo){
    if(campo == NULL){
        printf("[ERROR]\n");
        printf("in game.c: liberarCampo()\n");
        printf("Game field is NULL, cannot free memory\n");
        return;
    }

    int** campoInt = (int**)campo;
    for(int i = 0; i < ROWS; i++) {free(campoInt[i]);}
    free(campoInt);
}
/* =================================================================================================================== */



/* =============================================== FUNÇÕES SECUNDÁRIAS =============================================== */
/* =================================================================================================================== */
