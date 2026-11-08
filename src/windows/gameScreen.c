#include "screen.h"

#include <stdio.h>

#include "jogador.h"

static void Init(Game game){
    UNUSED(game);

    Jogador j = criarJogador(10);

    bool suc = carregarBaralho(j, true, "./assets/data/cartas.json");
    if(!suc) printf("\n\nErro ao carregar baralho :(\n\n");

    embaralharBaralho(j);

    printBaralho(j);
}

static void Update(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);
}

static void Draw(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);
}

static void Unload(Game game){
    UNUSED(game);
}

Screen GameScreen = { Init, Update, Draw, Unload };