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
    char* sprite;
    bool playerFlag;
}carta;

Carta criarCarta(int id, char* nome, int atk, int vida, char* sprite, bool playerFlag){
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

    // 3: Aloca memória para o sprite da carta e copia o caminho fornecido para a estrutura da carta
    c->sprite = (char*)malloc((strlen(sprite) + 1) * sizeof(char));
    if(c->sprite == NULL){
        printf("[ERROR]: criarCarta() [carta.c]\n");
        printf("Card [sprite] memory allocation failed\n");
        free(c->nome);
        free(c);
        return NULL;
    }
    strcpy(c->sprite, sprite);

    // 4: Inicializa os atributos da carta com os valores fornecidos
    c->id   = id;
    c->atk  = atk;
    c->vida = vida;
    c->playerFlag = playerFlag;
    c->pos[0] = 0;
    c->pos[1] = 0;
    c->sprite = NULL; // Inicializa o sprite como NULL, pode ser definido posteriormente

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

char* getNome(Carta c) {return ((carta *)c)->nome;}

int  getAtk(Carta c)          {return ((carta *)c)->atk;}
void setAtk(Carta c, int atk) {((carta *)c)->atk = atk;}

int  getVida(Carta c)           {return ((carta *)c)->vida;}
void setVida(Carta c, int vida) {((carta *)c)->vida = vida;}

int  getPosX(Carta c)            {return ((carta *)c)->pos[0];}
int  getPosY(Carta c)            {return ((carta *)c)->pos[1];}
void setPos(Carta c, int pos[2]) {((carta *)c)->pos[0] = pos[0]; ((carta *)c)->pos[1] = pos[1];}

char* getSprite(Carta c) {return ((carta *)c)->sprite;}

bool getPlayerFlag(Carta c)                  {return ((carta *)c)->playerFlag;}
void setPlayerFlag(Carta c, bool playerFlag) {((carta *)c)->playerFlag = playerFlag;}
    



void killCarta(Item item, void* extra){
    // 1: Verifica se a carta é válida antes de liberar a memória alocada para ela
    if(item == NULL){
        printf("[ERROR]: killCarta() [carta.c]\n");
        printf("Card is NULL, cannot free memory\n");
        return;
    }

    // 2: Faz o cast do ponteiro genérico para o tipo específico da estrutura da carta
    carta* c_remove = (carta *)item;

    // 3: Libera a memória alocada para o nome da carta e para a própria estrutura da carta
    free(c_remove->nome);
    free(c_remove);
}