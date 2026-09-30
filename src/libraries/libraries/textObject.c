#include "textObject.h"

#include <raymath.h>

#include <stdlib.h>
#include <string.h>

#include <hash.h>

#include "utils.h"

Hash TxtAllInstances = NULL;

typedef struct TextAnimationResourcesStr{
    Animation* animation;
    float letterDelta;
} TextAnimationResourcesStr;

typedef struct TextAnimationStr{
    TextAnimationResourcesStr* x;
    TextAnimationResourcesStr* y;
} TextAnimationStr;

typedef struct TextObjectStr{
    int id;
    char text[MAX_STRSIZE];
    Vector2 position;
    int fontsize;

    Rectangle boundingBox;
    float padding;
    Color color;

    Font* fontBitmap;
    Font* fontTrueType;

    float spacing;

    TextAnimationStr* txtAnim;
} TextObjectStr;

TextObject Text_Init(const char* text){
    TextObjectStr* txt = (TextObjectStr*)malloc(sizeof(TextObjectStr));
    
    static int id = 0;

    txt->id = id;
    id += 1;

    strncpy(txt->text, text, MAX_STRSIZE - 1);
    txt->text[MAX_STRSIZE - 1] = '\0';

    txt->color = WHITE;
    txt->fontsize = 10;
    txt->position.x = txt->position.y = 0;
    txt->boundingBox = (Rectangle){txt->position.x, txt->position.y, MeasureText(txt->text, txt->fontsize), txt->fontsize};
    txt->padding = 0.0f;

    txt->fontBitmap = NULL;
    txt->fontTrueType = NULL;
    
    txt->spacing = 0.0f;

    txt->txtAnim = NULL;

    createAndInsertInstance(&TxtAllInstances, txt->id, txt);

    return (TextObject)txt;
}

TextObject Text_Copy(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    TextObjectStr* newTxt = (TextObjectStr*)Text_Init(txt->text);

    newTxt->fontsize = txt->fontsize;
    newTxt->color = txt->color;
    newTxt->boundingBox = txt->boundingBox;
    newTxt->position = txt->position;
    newTxt->padding = txt->padding;

    return (TextObject)newTxt;
}

static void Text_UpdateRec(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->boundingBox = (Rectangle){txt->position.x - txt->padding, txt->position.y - txt->padding, MeasureText(txt->text, txt->fontsize) + txt->padding * 2, txt->fontsize + txt->padding * 2};
}

void Text_Set(TextObject txtObj, const char* text){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    strncpy(txt->text, text, MAX_STRSIZE - 1);
    txt->text[MAX_STRSIZE - 1] = '\0';

    Text_UpdateRec(txt);
}

void Text_SetFontSize(TextObject txtObj, int fontSize){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->fontsize = fontSize;
    Text_UpdateRec(txt);
}

void Text_SetRecPadding(TextObject txtObj, float padding){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->padding = padding;
    Text_UpdateRec(txt);
}

void Text_Scale(TextObject txtObj, float scaling){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    int basefontsize = 20;
    float scale_font = (float)(GetScreenWidth() * scaling) / MeasureText(txt->text, basefontsize);
    txt->fontsize = basefontsize * scale_font;
}

void Text_SetPosition(TextObject txtObj, Vector2 position){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->boundingBox.x = position.x;
    txt->boundingBox.y = position.y;

    txt->position.x = txt->boundingBox.x + txt->padding;
    txt->position.y = txt->boundingBox.y + txt->padding;

    if(txt->txtAnim){
        Animation_SetPosition(txt->txtAnim->x->animation, txt->position);
        Animation_SetPosition(txt->txtAnim->y->animation, txt->position);
    }
}

void Text_SetColor(TextObject txtObj, Color color){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->color = color;
}

void Text_SetSpacing(TextObject txtObj, float spacing){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->spacing = spacing;
}

bool Text_IsPointOverText(TextObject txtObj, Vector2 point){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return CheckCollisionPointRec(point, txt->boundingBox);
}

void Text_MoveDelta(TextObject txtObj, Vector2 delta){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->boundingBox.x += delta.x;
    txt->boundingBox.y += delta.y;
    
    txt->position.x = txt->boundingBox.x + txt->padding;
    txt->position.y = txt->boundingBox.y + txt->padding;

    if(txt->txtAnim){
        Animation_SetPosition(txt->txtAnim->x->animation, txt->position);
        Animation_SetPosition(txt->txtAnim->y->animation, txt->position);
    }
}

void Text_AssignBitmapFont(TextObject txtObj, Font* font){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->fontBitmap = font;
}

void Text_AssignTrueTypeFont(TextObject txtObj, Font* font){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    txt->fontTrueType = font;
}

static TextAnimationResourcesStr* Text_InitAnimationResources(TextObjectStr* txt, interpolationFunction interFunc, float letterDelta){
    TextAnimationResourcesStr* tar = (TextAnimationResourcesStr*)malloc(sizeof(TextAnimationResourcesStr));

    tar->animation = Animation_Init();
    Animation_AddPositionAnimation(tar->animation, interFunc);
    Animation_SetPosition(tar->animation, txt->position);

    
    tar->letterDelta = letterDelta;
    
    return tar;
}

void Text_AddAnimation(TextObject txtObj, interpolationFunction interFuncX, float letterDeltaX, interpolationFunction interFuncY, float letterDeltaY){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    
    txt->txtAnim = (TextAnimationStr*)malloc(sizeof(TextAnimationStr));
    
    txt->txtAnim->x = Text_InitAnimationResources(txt, interFuncX, letterDeltaX);
    txt->txtAnim->y = Text_InitAnimationResources(txt, interFuncY, letterDeltaY);
}

void Text_Draw(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    
    Font font = txt->fontTrueType ? *txt->fontTrueType : (txt->fontBitmap ? *txt->fontBitmap : GetFontDefault());
    DrawTextEx(font, txt->text, txt->position, txt->fontsize, txt->spacing, txt->color);
}

static void Text_UpdateAnimation(TextObjectStr* txt, TextAnimationResourcesStr* txtRes){
    if(Animation_PositionIsAnimating(txtRes->animation) == false) Animation_MoveTo(txtRes->animation, txt->position, 0.75f);
}

void Text_DrawAnimated(TextObject txtObj, float deltaTime){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    
    Font font = txt->fontTrueType ? *txt->fontTrueType : (txt->fontBitmap ? *txt->fontBitmap : GetFontDefault());
    
    int codepointCount = 0;
    int* codepoints = LoadCodepoints(txt->text, &codepointCount);
    
    float xOffset = 0.0f;
    float scaleFactor = (float)txt->fontsize / font.baseSize;
    
    TextAnimationResourcesStr* xFuncs = txt->txtAnim->x;
    TextAnimationResourcesStr* yFuncs = txt->txtAnim->y;
    
    Text_UpdateAnimation(txt, xFuncs);
    Text_UpdateAnimation(txt, yFuncs);

    Animation_UpdatePosition(xFuncs->animation, deltaTime);
    Animation_UpdatePosition(yFuncs->animation, deltaTime);
    
    float xProgress = Animation_GetPositionProgress(xFuncs->animation);
    float yProgress = Animation_GetPositionProgress(yFuncs->animation);
    
    interpolationFunction xInterFunc = Animation_GetPositionFunction(xFuncs->animation);
    interpolationFunction yInterFunc = Animation_GetPositionFunction(yFuncs->animation);
    
    for(int i = 0; i < codepointCount; i++){
        int index = GetGlyphIndex(font, codepoints[i]);
        
        float offsetX = xInterFunc((xProgress + (i * xFuncs->letterDelta)));
        float offsetY = yInterFunc((yProgress + (i * yFuncs->letterDelta)));

        Vector2 charPos = { txt->position.x + xOffset + offsetX, txt->position.y + offsetY};
        
        DrawTextCodepoint(font, codepoints[i], charPos, (float)txt->fontsize, txt->color);
        
        if(font.glyphs[index].advanceX == 0) xOffset += (font.recs[index].width + txt->spacing) * scaleFactor;
        else xOffset += (font.glyphs[index].advanceX + txt->spacing) * scaleFactor;
    }
    
    UnloadCodepoints(codepoints);
}

int Text_getId(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return txt->id;
}

Rectangle Text_getRectangle(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return txt->boundingBox;
}

int Text_getTextLength(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return (int)strlen(txt->text);
}

float Text_getLength(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return (float)MeasureText(txt->text, txt->fontsize);
}

const char* Text_getText(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return TextFormat("%s", txt->text);
}

float Text_getPadding(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    return txt->padding;
}

static void Text_FreeInstance(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    
    free(txt);
}

void Text_Free(TextObject txtObj){
    TextObjectStr* txt = (TextObjectStr*)txtObj;
    removeInstance(TxtAllInstances, txt->id);

    Text_FreeInstance(txtObj);
}

void Text_FreeAll(){
    destroiHash(TxtAllInstances, freeExtra, Text_FreeInstance);
    TxtAllInstances = NULL;
}