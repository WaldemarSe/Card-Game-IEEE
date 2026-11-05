#include "cartaInterface.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <stdio.h>

#include <animation.h>
#include <lista.h>

Hash cardsAllInstances = NULL;

typedef struct CardStr {
    int id;

    Texture2D img;
    Animation anim;
    
    Rectangle rect;
    Vector2 lastPosition;

    float scaleRatio;

    bool hovered;
    bool grabbed;
    bool attached;

    float rotation;

    CurrentScale scaleType;
    float time;

    Color cor;
} CardStr;

Card Card_Init(Rectangle rect, Texture2D txr){
    CardStr* card = (CardStr*)malloc(sizeof(CardStr));
    
    static int id = 0;

    card->id = id;
    card->img = txr;

    card->anim = Animation_Init();
    Animation_AddPositionAnimation(card->anim, easeOutBack);
    Animation_AddScaleAnimation(card->anim, rect, easeOutBack);

    card->rect = rect;
    card->lastPosition = (Vector2){rect.x, rect.y};
    card->scaleRatio = 1.0f;

    card->hovered = false;
    card->grabbed = false;
    card->attached = false;
    
    card->rotation = 0.0f;

    card->cor = WHITE;

    card->scaleType = MAXIMIZED;
    card->time = 0.0f;

    createAndInsertInstance(&cardsAllInstances, id, card);

    id += 1;
    
    return card;
}

Rectangle Card_GetRect(Card card){
    return ((CardStr*)card)->rect;
}

int Card_GetId(Card card){
    return ((CardStr*)card)->id;
}

Card Card_GetById(int id){
    return getHashValue(cardsAllInstances, TextFormat("%d", id));
}

bool Card_isHovered(Card card, Vector2 point){
    CardStr* c = (CardStr*)card;

    c->hovered = CheckCollisionPointRec(point, c->rect);

    return c->hovered;
}

bool Card_isGrabbed(Card card, bool isDown){
    CardStr* c = (CardStr*)card;

    if(c->grabbed){
        c->grabbed = isDown;
        c->attached = c->grabbed;
    }
    else c->grabbed = c->hovered && isDown;

    return c->attached;
}

void Card_SetRotation(Card card, float rotation){
    ((CardStr*)card)->rotation = rotation;
}

void Card_Move(Card card, Vector2 delta){
    CardStr* c = (CardStr*)card;

    c->rect.x += delta.x;
    c->rect.y += delta.y;
}

void Card_MoveTo(Card card, Vector2 finalPoint, float duration){
    CardStr* c = (CardStr*)card;

    Vector2 fPoint;
    fPoint.x = finalPoint.x - c->rect.width/2;
    fPoint.y = finalPoint.y - c->rect.height/2;

    Vector2 cPos = (Vector2){c->rect.x, c->rect.y};

    Animation_SetPosition(c->anim, cPos);
    Animation_MoveTo(c->anim, fPoint, duration);
}

void Card_Wiggle(Card card, float deltaTime){
    CardStr* c = (CardStr*)card;

    c->rotation = sin(c->time * 18) * PI/2;
    c->time = c->time + deltaTime;
}

void Card_SetScaleRatio(Card card, float scaleRatio){
    ((CardStr*)card)->scaleRatio = scaleRatio;
}

void Card_SetScale(Card card, float scale, float duration){
    CardStr* c = (CardStr*)card;

    if(Animation_ScaleIsAnimating(c->anim)) Animation_EndResize(c->anim);
    c->rect = Animation_GetScale(c->anim);
    
    Animation_Resize(c->anim, scale, duration);
}

void Card_Minimize(Card card, float duration){
    CardStr* c = (CardStr*)card;
    
    if(c->scaleType == MINIMIZED) return;
    
    Card_SetScale(card, c->scaleRatio, duration);
    
    c->scaleType = MINIMIZED;
}

void Card_Medianize(Card card, float duration){
    CardStr* c = (CardStr*)card;

    if(c->scaleType == MEDIANIZED) return;

    Card_SetScale(card, ((1.0f - c->scaleRatio) * 0.5f) + c->scaleRatio, duration);
    
    c->scaleType = MEDIANIZED;
}

void Card_Maximize(Card card, float duration){
    CardStr* c = (CardStr*)card;

    if(c->scaleType == MAXIMIZED) return;

    Card_SetScale(card, 1.0f, duration);
    
    c->scaleType = MAXIMIZED;
}

static void Card_UpdatePos(Card card, float deltaTime){
    CardStr* c = (CardStr*)card;

    Animation_UpdatePosition(c->anim, deltaTime);
    
    if(!Animation_PositionIsAnimating(c->anim)) return;
    
    Vector2 pos = Animation_GetPosition(c->anim);
    c->rect.x = pos.x;
    c->rect.y = pos.y;
}

static void Card_UpdateSize(Card card, float deltaTime){
    CardStr* c = (CardStr*)card;

    Animation_SetRectangle(c->anim, c->rect);
    Animation_UpdateScale(c->anim, deltaTime);
    
    if(!Animation_ScaleIsAnimating(c->anim)) return;
    
    Rectangle scale = Animation_GetScale(c->anim);
    c->rect = scale;
}

void Card_Update(Card card, float deltaTime){
    CardStr* c = (CardStr*)card;

    Card_UpdatePos(card, deltaTime);
    Card_UpdateSize(card, deltaTime);

    // c->img.width = c->rect.width;
    // c->img.height = c->rect.height;
}

void Card_UpdateLastPosition(Card card){
    CardStr* c = (CardStr*)card;

    c->lastPosition = (Vector2){c->rect.x, c->rect.y};
}

Vector2 Card_GetPosition(Card card){
    CardStr* c = ((CardStr*)card);
    return (Vector2){c->rect.x, c->rect.y};
}

Vector2 Card_GetLastPosition(Card card){
    return ((CardStr*)card)->lastPosition;
}

float Card_GetRotation(Card card){
    return ((CardStr*)card)->rotation;
}

void Card_Draw(Card card){
    CardStr* c = (CardStr*)card;

    Rectangle source = (Rectangle){0, 0, c->img.width, c->img.height};
    Rectangle dest = (Rectangle){
        c->rect.x + c->rect.width / 2.0f,
        c->rect.y + c->rect.height / 2.0f,
        c->rect.width,
        c->rect.height
    };
    Vector2 origin = (Vector2){c->rect.width / 2.0f, c->rect.height / 2.0f};

    DrawTexturePro(c->img, source, dest, origin, c->rotation, WHITE);
}

Texture2D Card_free(Card card){
    CardStr* c = (CardStr*)card;
    Texture2D txr = c->img;
    
    Animation_Free(c->anim);

    removeInstance(cardsAllInstances, c->id);
    free(c);

    return txr;
}

bool compararCartas(Card card, Item id){
    CardStr* c = (CardStr*)card;
    int cId = *(int*)id;

    return (c->id == cId);
}