#include "screen.h"

#include <raymath.h>

#include <imageObject.h>
#include <textObject.h>
#include <button.h>

#define CLEARCOLOR (Color){0, 0, 0, 0}

static ImageObject background = NULL;
static TextObject title = NULL;
static Button startButton = NULL;

static float mySinf(float t){
    return sinf(2.0f * PI * t) * 2.0f;
}

static void Init(Game game){
    Font* gameFont = Game_GetFont(game);

    // Imagem de placeholder
    background = Image_Init("./assets/sprites/menuBackground_p.png");
    Image_FitToScreenSize(background);
    Image_SetColor(background, (Color){255, 255, 255, 100});

    title = Text_Init("CompCardGame");
    Text_AddAnimation(title, cosf, 0.0f, mySinf, 0.1f);
    Text_SetFontSize(title, 40);
    Text_SetSpacing(title, 1.8f);
    Text_SetPosition(title, CENTER);

    Text_AssignTrueTypeFont(title, gameFont);

    startButton = Button_Init("Start", 40, Vector2AddValue(CENTER, 40), WHITE, CLEARCOLOR, RED, CLEARCOLOR);
    Button_AssignTrueTypeFont(startButton, gameFont);
}

static void Update(Game game, float deltaTime){
    if(Button_isPressedByMouse(startButton)){
        ChangeScreen(GAMESCREEN);
    }
}

static void Draw(Game game, float deltaTime){
    Image_Draw(background);
    Text_DrawAnimated(title, deltaTime);
    Button_Draw(startButton);
}

static void Unload(Game game){
    Image_FreeAll();
    Text_FreeAll();
    Button_Free(startButton);

    background = NULL;
    title = NULL;
    startButton = NULL;
}

Screen MenuScreen = { Init, Update, Draw, Unload };