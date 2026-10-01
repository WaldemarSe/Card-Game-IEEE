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
    int pos[2];
    bool playerFlag;
}carta;

Carta* criarCarta(int id, char* nome, int atk, int vida, bool playerFlag){
    // 1: Aloca memória para a estrutura da carta
    carta* c = (carta*)malloc(sizeof(carta));
    if(c == NULL){
        printf("[ERROR]: criarCarta() [carta.c]\n");
        printf("Card memory allocation failed\n");
        return NULL;
    }

    // 2: Aloca memória para o nome da carta e copia o nome fornecido para a estrutura da carta
    c->nome = (char*)malloc((strlen(nome) + 1) * sizeof(char));
    if(c->nome == NULL){
        printf("[ERROR]: criarCarta() [carta.c]\n");
        printf("Card [name] memory allocation failed\n");
        free(c);
        return NULL;
    }
    strcpy(c->nome, nome);

    // 3: Inicializa os atributos da carta com os valores fornecidos
    c->id   = id;
    c->atk  = atk;
    c->vida = vida;
    c->playerFlag = playerFlag;
    c->pos[0] = 0;
    c->pos[1] = 0;

    // printf("[INFO]: criarCarta() [carta.c]\n");
    // printf("Card [%d] created successfully\n", c->id);
    // printf("Name: %s\n", c->nome);
    // printf("Attack: %d\n", c->atk);
    // printf("Life: %d\n", c->vida);
    // printf("Position: [%d, %d]\n", c->pos[0], c->pos[1]);
    // printf("Flag: %s\n\n", c->playerFlag ? "Player" : "Opponent");

    // 5: Retorna o ponteiro para a carta criada
    return (Carta*)c;
}

int getID(Carta c) {return ((carta *)c)->id;}

int  getAtk(Carta c)          {return ((carta *)c)->atk;}
void setAtk(Carta c, int atk) {((carta *)c)->atk = atk;}

int  getVida(Carta c)           {return ((carta *)c)->vida;}
void setVida(Carta c, int vida) {((carta *)c)->vida = vida;}

int  getPosX(Carta c)            {return ((carta *)c)->pos[0];}
int  getPosY(Carta c)            {return ((carta *)c)->pos[1];}
void setPos(Carta c, int pos[2]) {((carta *)c)->pos[0] = pos[0]; ((carta *)c)->pos[1] = pos[1];}

bool getPlayerFlag(Carta c)                  {return ((carta *)c)->playerFlag;}
void setPlayerFlag(Carta c, bool playerFlag) {((carta *)c)->playerFlag = playerFlag;}
    



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
    free(c_remove->nome);
    free(c_remove);
}