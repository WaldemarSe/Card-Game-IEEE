#ifndef _JOGADOR_H_
#define _JOGADOR_H_
    
typedef void* Jogador;

Jogador* criarJogador(int vida);
void setVidaJogador(Jogador* jogador, int vida);
int getVidaJogador(Jogador* jogador);

#endif