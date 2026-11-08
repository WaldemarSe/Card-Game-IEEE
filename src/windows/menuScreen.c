#include "screen.h"

#include <raymath.h>

#include <imageObject.h>
#include <textObject.h>
#include <button.h>

#define CLEARCOLOR (Color){0, 0, 0, 0}

static ImageObject background = NULL;
static TextObject title = NULL;

static Button startButton = NULL;
static Button testButton = NULL;

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
    Text_SetPosition(title, Vector2Zero());

    Text_AssignTrueTypeFont(title, gameFont);

    startButton = Button_Init("Start", 40, Vector2Zero(), WHITE, CLEARCOLOR, RED, CLEARCOLOR);
    Button_AssignTrueTypeFont(startButton, gameFont);
    Button_CentralizeOnPoint(startButton, CENTER);

    testButton = Button_Init("Testes", 40, Vector2AddValue(CENTER, 40), WHITE, CLEARCOLOR, RED, CLEARCOLOR);
    Button_AssignTrueTypeFont(testButton, gameFont);

    Rectangle startBRec = Button_GetRec(startButton);
    Vector2 testBPos = (Vector2){CENTER.x, startBRec.y + startBRec.height * 1.5f};

    Button_CentralizeOnPoint(testButton, testBPos);
}

static void Update(Game game, float deltaTime){
    UNUSED(game);
    UNUSED(deltaTime);

    if(Button_isPressedByMouse(startButton)){
        ChangeScreen(GAMESCREEN);
    }
    else if(Button_isPressedByMouse(testButton)){
        ChangeScreen(TESTSCREEN);
    }
}

static void Draw(Game game, float deltaTime){
    UNUSED(game);

    Image_Draw(background);
    Text_DrawAnimated(title, deltaTime);
    Button_Draw(startButton);
    Button_Draw(testButton);
}

static void Unload(Game game){
    UNUSED(game);

    Image_FreeAll();
    Text_FreeAll();
    Button_Free(startButton);
    Button_Free(testButton);

    background = NULL;
    title = NULL;
    startButton = NULL;
    testButton = NULL;
}

Screen MenuScreen = { Init, Update, Draw, Unload };