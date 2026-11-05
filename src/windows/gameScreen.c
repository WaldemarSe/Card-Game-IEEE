#include "screen.h"

#include <stdio.h>
#include <raymath.h>

#include <imageObject.h>
#include <textObject.h>
#include <button.h>
#include <fileHandler.h>

#include <lista.h>

#include "campo.h"
#include "carta.h"

#include "campoInterface.h"
#include "cartainterface.h"

static TextObject title = NULL;

static Campo campo = NULL;
static Field field = NULL;

static Lista cartasJogador = NULL;
static Lista cartasInimigo = NULL;

static Lista cardsList = NULL;

static Texture2D* cardSprites = NULL;

static float mySinf(float t){
    return sinf(2.0f * PI * t) * 2.0f;
}

static void openDirectoryAndLoadSprites(){
    char* path = "./assets/sprites/cards/";

    // Abre o path para leitura dos nomes das cartas
    DIR* dir = Directory_Open(path);
    
    FilesInfo finfo = Directory_ReadFiles(dir);
    char** nomes = Directory_GetFileNames(finfo);
    int nFiles = Directory_GetNumFiles(finfo);

    cardSprites = (Texture2D*)malloc(sizeof(Texture2D) * nFiles);

    // Carrega a textura das cartas
    for(int i = 0; i < nFiles; i++){
        cardSprites[i] = LoadTexture(TextFormat("%s%s", path, nomes[i]));
        printf("\nCard Loaded: %s", nomes[i]);
    }

    // Fecha o path de leitura
    Directory_FreeFilesInfo(finfo);
    Directory_Close(dir);
}

static void Init(Game game){
    Font* gameFont = Game_GetFont(game);
    
    title = Text_Init("Game Screen");
    Text_AddAnimation(title, cosf, 0.0f, mySinf, 0.1f);
    Text_SetFontSize(title, 40);
    Text_SetSpacing(title, 1.8f);
    Text_SetPosition(title, CENTER);
    
    Text_AssignTrueTypeFont(title, gameFont);
    
    // 0.5: Abre o diretório dos sprites das cartas e carrega em um array
    openDirectoryAndLoadSprites();
    
    // 1: Cria o campo de jogo
    campo = criarCampo();
    field = Field_Init((Rectangle){0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}, (Texture2D){0}, 5);
    
    // 2: Cria algumas cartas para testar as funções do jogo e adiciona no campo
    // 2.a: Cards (interfaces)
    cardsList = criaLista();
    
    float centerX = -SCREEN_WIDTH/2;
    float centerY = -SCREEN_HEIGHT/2;
    Rectangle centerCardPos = (Rectangle){centerX, centerY, 120, 180};
    
    for(int i = 0; i < 4; i++){
        Card c = Card_Init(centerCardPos, cardSprites[i]);
        Card_SetScaleRatio(c, 0.80f);
        Card_SetScale(c, 0.80f, 0.0f);
        
        inserirFim(cardsList, c);
    }
    
    // 2.b: Cartas (entities)
    int attr[4][2] = {{1, 1}, {5, 5}, {1, 1}, {10, 10}};
    
    cartasJogador = criaLista();
    cartasInimigo = criaLista();
    
    for(int i = 0; i < 4; i++){
        Carta carta = criarCarta(TextFormat("Carta %i", i), attr[i][0], attr[i][1]);
        adicionarCarta(campo, carta, (i <= 1), i);
        
        int id = getID(carta);
        Card card = Card_GetById(id);
        Card_MoveTo(card, CENTER, 5.0f);

        if(i <= 1) inserirFim(cartasJogador, carta);
        else inserirFim(cartasInimigo, carta);
    }

    Field_AssignMatrixObject(field, campo, getItemFromPositionCampo, 3, 4);
}

static void Card_UpdateVoid(Item item, void* extra){
    Vector2 pos = Card_GetPosition(item);
    printf("\n %.1f, %.1f", pos.x, pos.y);
    
    Card_Update(item, *(float*)extra);
}

static void Update(Game game, float deltaTime){
    percorrerLista(cardsList, Card_UpdateVoid, &deltaTime);

    if(IsKeyPressed(KEY_W)) atacarCarta(campo, getItemLista(cartasJogador, 1), getItemLista(cartasInimigo, 1));
    if(IsKeyPressed(KEY_S)) atacarCarta(campo, getItemLista(cartasInimigo, 1), getItemLista(cartasJogador, 1));
}

static void Draw(Game game, float deltaTime){
    Text_DrawAnimated(title, deltaTime);

    percorrerLista(cardsList, runExtra, Card_Draw);
    //Field_DrawFromMatrixObject(field);
}

static void Unload(Game game){
    limparLista(cartasJogador, NULL, NULL);
    limparLista(cartasInimigo, NULL, NULL);
    liberarCampo(campo);
    
    Text_FreeAll();

    title = NULL;
}

Screen GameScreen = { Init, Update, Draw, Unload };