#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "carta.h"

/*
    Um exemplo de como ficariam os arquivos .h
*/

typedef struct{
    int id;
    char* nome;
    int atk;
    int vida;
    int pos;
    bool playerFlag;
}carta;

Carta* criarCarta(int id, char* nome, int atk, int vida){
    carta* c = (carta*)malloc(sizeof(carta));
    if(c == NULL){
        printf("[ERROR]\n");
        printf("in carta.c: criarCarta()\n");
        printf("Card memory allocation failed\n");
        return NULL;
    }

    c->nome = (char*)malloc((strlen(nome) + 1) * sizeof(char));
    if(c->nome == NULL){
        printf("[ERROR]\n");
        printf("in carta.c: criarCarta()\n");
        printf("Card name memory allocation failed\n");
        free(c);
        return NULL;
    }
    strcpy(c->nome, nome);

    c->id   = id;
    c->atk  = atk;
    c->vida = vida;

    // printf("[INFO]: criarCarta() [carta.c]\n");
    // printf("Card created successfully:\n");
    // printf("ID: [%d], Name: [%s], ATK: [%d], Vida: [%d]\n\n", c->id, c->nome, c->atk, c->vida);

    return (Carta*)c;
}

int getAtk(Carta c){
    return ((carta *)c)->atk;
}

int getVida(Carta c){
    return ((carta *)c)->vida;
}

int getID(Carta c){
    if(c == NULL) {return 0;}
    else          {return ((carta *)c)->id;}
}

int getPos(Carta c){
    return ((carta *)c)->pos;
}

bool getPlayerFlag(Carta c){
    return ((carta *)c)->playerFlag;
}

void setPlayerFlag(Carta c, bool playerFlag){
    ((carta *)c)->playerFlag = playerFlag;
}
    
void setPos(Carta c, int pos){
    ((carta *)c)->pos = pos;
}

void setVida(Carta c, int vida){
    ((carta *)c)->vida = vida;
}

void setAtk(Carta c, int atk){
    ((carta *)c)->atk = atk;
}

void killCarta(Carta c){
    if(c == NULL){
        printf("[ERROR]\n");
        printf("in carta.c: killCarta()\n");
        printf("Card is NULL, cannot free memory\n");
        return;
    }

    carta* c_remove = (carta *)c;

    // printf("[INFO]: killCarta() [carta.c]\n");
    // printf("Freeing card memory: [%p]\n", (void*)c_remove);

    free(c_remove->nome);
    free(c_remove);

    // printf("Card [%p]: Memory freed successfully\n\n", (void*)c_remove);
}