#include <stdio.h>
#include <stdlib.h>

#include "carta.h"

/*
    Um exemplo de como ficariam os arquivos .h
*/

typedef struct{
    char* nome;
    int atk;
    int vida;
}carta;

int getAtk(Carta c){
    return ((carta *)c)->atk;
}

int getVida(Carta c){
    return ((carta *)c)->vida;
}

void setVida(Carta c, int vida){
    ((carta *)c)->vida = vida;
}

void setAtk(Carta c, int atk){
    ((carta *)c)->atk = atk;
}

void killCarta(Carta c){
    carta* c_remove = (carta *)c;
    
    free(c_remove->nome);
    free(c_remove);
}