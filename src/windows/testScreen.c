#include "screen.h"

#include <stdio.h>

#include <delimiters.h>

#include "cartainterface.h"

/** TELA DE TESTE
 * 
 * Pode ser usada livremente, mas lembre-se de desmarcar na hora de fazer commit para evitar conflitos depois.
 * NOTA:    Variáveis usadas em múltiplas função devem ser declaradas como estáticas globalmente.
 * 
 * INIT:    Serve para inicalização de variáveis.
 * 
 * UPDATE:  Itens que requerem atualizações constantes (por frame), por ex: verificação de vida > 0.
 * 
 * DRAW:    Atualiza todo frame para desenhar na tela (caso deseje testar prints, coloque no INIT ou com um
 *              [if(keypressed(...) printf();] no UPDATE.).
 * 
 * UNLOAD:  Liberação de variáveis alocadas.
*/

static void Card_ResizeAnimation(Card c, Vector2 mousePos){
    if(Card_isHovered(c, mousePos)){
        if(Card_isGrabbed(c, mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
            Card_Maximize(c, 0.5f);
        }
        else Card_Medianize(c, 0.5f);
    }
    else Card_Minimize(c, 0.5f);
}

static void Card_DragCheck(Card c, Vector2 mousePos, Vector2 mouseDelta){
    if(Card_isGrabbed(c, mousePos, IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
        Card_Move(c, mouseDelta);
    }
}

// Exemplo de variável estática global para ser acessada em múltiplas partes do arquivo.
Card c1 = NULL;

static void Init(Game game){
    UNUSED(game);

    Vector2 wh = {200 * 3.0f/4.0f, 200};
    Rectangle center = {CENTER.x - wh.x / 2.0f, CENTER.y - wh.y / 2.0f, wh.x, wh.y};

    Texture2D txr = LoadTexture("./assets/sprites/cards/c1.png");
    c1 = Card_Init(center, txr);
}

static void Update(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);

    Vector2 mousePos = GetMousePosition();
    Vector2 mouseDelta = GetMouseDelta();

    if(IsKeyPressed(KEY_W)) Card_PlayAttackAnimation(c1, (Vector2){CENTER.x - 100/2.0f, 0});
    
    Card_ResizeAnimation(c1, mousePos);
    if(!Card_isOnAnimation(c1)) Card_DragCheck(c1, mousePos, mouseDelta);

    Card_Update(c1, deltaTime);
}

static void Draw(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);

    Card_Draw(c1);
}

static void Unload(Game game){
    UNUSED(game);

    Texture2D txr = Card_free(c1);
    UnloadTexture(txr);
}

Screen TestScreen = { Init, Update, Draw, Unload };