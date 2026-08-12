#ifndef card_h
#define card_h

/*
    Um exemplo de como ficariam os arquivos .h
*/

typedef void* Carta; // Ponteiro para o Card

int getAtk(Carta c);

void setAtk(Carta c, int atk);

int getVida(Carta c);

void setVida(Carta c, int vida);

void killCarta(Carta c);

#endif