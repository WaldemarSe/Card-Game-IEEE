#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "carta.h"

#include <delimiters.h>

/*
    Um exemplo de como ficariam os arquivos .h
*/

typedef struct{
    int id;
    char spritePath[MAX_STRSIZE];

    char nome[MAX_STRSIZE];
    int atk;
    int vida;
    
    int pos[2];

    bool playerFlag;
}carta;

Carta criarCarta(const char* nome, int atk, int vida, const char* spritePath, bool playerFlag){
    // 1: Aloca memória para a estrutura da carta
    carta* c = (carta*)malloc(sizeof(carta));
    if(c == NULL){
        printf("[ERROR]: criarCarta() [carta.c]\n");
        printf("Card memory allocation failed\n");
        return NULL;
    }

    static int id = 0;

    // 2: Inicializa os atributos da carta com os valores fornecidos
    c->id   = id++;
    
    c->atk  = atk;
    c->vida = vida;

    c->pos[0] = 0;
    c->pos[1] = 0;

    c->playerFlag = playerFlag;

    // 3: Aloca memória para o nome da carta e copia o nome fornecido para a estrutura da carta
    strncpy(c->nome, nome, MAX_STRSIZE);
    c->nome[sizeof(c->nome) - 1] = '\0';

    // 4: Aloca memória para o sprite da carta e copia o caminho fornecido para a estrutura da carta
    strncpy(c->spritePath, spritePath, MAX_STRSIZE);
    c->spritePath[sizeof(c->spritePath) - 1] = '\0';
    
    // 5: Retorna o ponteiro para a carta criada
    return c;
}

int getID(Carta c){
    return ((carta *)c)->id;
}

const char* getNome(Carta c){
    carta* card = (carta *)c;
    return TextFormat("%s", card->nome);
}

int getAtk(Carta c){
    return ((carta *)c)->atk;
}

int getVida(Carta c){
    return ((carta *)c)->vida;
}

int getPosX(Carta c){
    return ((carta *)c)->pos[0];
}

int getPosY(Carta c){
    return ((carta *)c)->pos[1];
}

const char* getSpritePath(Carta c){
    carta* card = (carta *)c;
    return TextFormat("%s", card->spritePath);
}

bool getPlayerFlag(Carta c){
    return ((carta *)c)->playerFlag;
}

void setAtk(Carta c, int atk){
    ((carta *)c)->atk = atk;
}

void setVida(Carta c, int vida){
    ((carta *)c)->vida = vida;
}

void setPos(Carta c, int pos[2]){
    ((carta *)c)->pos[0] = pos[0];
    ((carta *)c)->pos[1] = pos[1];
}

void setPlayerFlag(Carta c, bool playerFlag){
    ((carta *)c)->playerFlag = playerFlag;
}

void killCarta(Carta c){
    // 1: Verifica se a carta é válida antes de liberar a memória alocada para ela
    if(c == NULL){
        printf("[ERROR]: killCarta() [carta.c]\n");
        printf("Card is NULL, cannot free memory\n");
        return;
    }

    // 2: Faz o cast do ponteiro genérico para o tipo específico da estrutura da carta
    carta* c_remove = (carta *)c;

    // 3: Libera a memória alocada para o nome da carta e para a própria estrutura da carta
    free(c_remove);
}

// AUXILIAR
void printCarta(Carta c){
    if(c == NULL){
        printf("[ERROR]: printCarta() [carta.c]\n");
        printf("Card is NULL, cannot print\n");
        return;
    }

    carta* card = (carta*)c;

    printf("[INFO]: printCarta() [carta.c]\n");
    printf("Card ID: %d\n", card->id);
    printf("Name: %s\n", card->nome);
    printf("Attack: %d\n", card->atk);
    printf("Life: %d\n", card->vida);
    printf("Position: [%d, %d]\n", card->pos[0], card->pos[1]);
    printf("Sprite Path: %s\n", card->spritePath);
    printf("Belongs to: %s\n\n", card->playerFlag ? "Player" : "Opponent");
}