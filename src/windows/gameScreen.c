#include "screen.h"

#include <stdio.h>

#include <delimiters.h>

#include "campo.h"
#include "jogador.h"

#include "campoInterface.h"
#include "cartainterface.h"

static Jogador jogador = NULL;
static Jogador inimigo = NULL;

static Campo campo = NULL;

static Field field = NULL;

static void Init(Game game){
    UNUSED(game);

    jogador = criarJogador(10);

    bool suc = carregarBaralho(jogador, true, "./assets/data/cartas.json");
    if(!suc) printf("\n\nErro ao carregar baralho :(\n\n");

    embaralharBaralho(jogador);

    printBaralho(jogador);

    inimigo = criarJogador(10);

    suc = carregarBaralho(inimigo, false, "./assets/data/cartas.json");
    if(!suc) printf("\n\nErro ao carregar baralho :(\n\n");

    embaralharBaralho(inimigo);

    printBaralho(inimigo);

    ///////////////////////////////////////////////////////

    campo = criarCampo();

    suc = comprarCarta(jogador);
    if(!suc) printf("\n\nErro ao comprar carta do jogador :(\n\n");
    suc = comprarCarta(inimigo);
    if(!suc) printf("\n\nErro ao comprar carta do inimigo :(\n\n");

    Lista jMao = getMaoJogador(jogador);
    Lista iMao = getMaoJogador(inimigo);

    Carta carta = removerInicio(jMao);
    adicionarCarta(campo, carta, 2);
    carta = removerInicio(iMao);
    adicionarCarta(campo, carta, 2);

    printCampo(campo);

    ///////////////////////////////////////////////////////

    // moverCartas(campo);
    // printCampo(campo);

    // atacarCartas(campo, true, jogador);
    // atacarCartas(campo, true, jogador);

    // atacarCartas(campo, true, jogador);

    // printCampo(campo);

    ///////////////////////////////////////////////////////

    Texture2D txr = LoadTexture("./assets/sprites/menuBackground_p.png");

    Rectangle fieldRec = {CENTER.x - SCREEN_WIDTH / 4.0f, CENTER.y - SCREEN_HEIGHT / 4.0f, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
    field = Field_Init(fieldRec, txr, 10);

    Field_AssignMatrixObject(field, campo, getCartaFromPos, 3, 4);
}

static void Update(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);

    Field_Update(field, deltaTime);
}

static void Draw(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);

    Field_Draw(field);
}

static void Unload(Game game){
    UNUSED(game);

    Lista cartasCampo = liberarCampo(campo);
    destroiLista(cartasCampo, runExtra, killCarta);
    liberarJogador(jogador);
}

Screen GameScreen = { Init, Update, Draw, Unload };