#ifndef _JOGADOR_H_
#define _JOGADOR_H_

#include <stdbool.h>

#include "../libraries/data_structures/lista.h"
    
typedef void* Jogador;

Jogador criarJogador(int vida);
void setVidaJogador(Jogador jogador, int vida);
int getVidaJogador(Jogador jogador);
Lista getMaoJogador(Jogador jogador);
Lista getBaralhoJogador(Jogador jogador);
bool carregarBaralho(Jogador jogador, bool playerFlag, const char* caminhoArquivo);
bool comprarCarta(Jogador jogador);
void liberarJogador(Jogador jogador);

#endif