#include <stdio.h>
#include <stdlib.h>

typedef struct jogador{
    int vida;
}Jogador;

Jogador* criarJogador(int vida){
    Jogador* jogador = (Jogador*)malloc(sizeof(Jogador));
    if(jogador == NULL){
        printf("[ERROR]: criarJogador() [jogador.c]\n");
        printf("Failed to allocate memory for player\n");
        return NULL;
    }
    jogador->vida = vida;
    return jogador;
}
void setVidaJogador(Jogador* jogador, int vida){
    if(jogador == NULL){
        printf("[ERROR]: setVidaJogador() [jogador.c]\n");
        printf("Player is NULL, cannot set life\n");
        return;
    }
    jogador->vida = vida;
}

int getVidaJogador(Jogador* jogador){
    if(jogador == NULL){
        printf("[ERROR]: getVidaJogador() [jogador.c]\n");
        printf("Player is NULL, cannot get life\n");
        return -1;
    }
    return jogador->vida;
}