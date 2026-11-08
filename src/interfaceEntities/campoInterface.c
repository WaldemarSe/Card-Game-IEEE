#include "campoInterface.h"

#include <stdlib.h>
#include <stdio.h>

#include <animation.h>

#include "carta.h"
#include "cartainterface.h"

typedef struct FieldStr {
    int id;

    Texture2D img;
    Animation anim;

    Rectangle rect;
    Vector2 lastPosition;

    float scaleRatio;

    bool hovered;

    float rotation;

    CurrentFieldScale scaleType;
    float time;

    Color cor;

    Lista content;
    int maxItems;

    Item matrix;
    getItemFuncMatrix matrixFunc;
    int matrixSizeX;
    int matrixSizeY;
} FieldStr;

Field Field_Init(Rectangle rect, Texture2D txr, int maxItems){
    FieldStr* f = malloc(sizeof(FieldStr));
    if(f == NULL){
        printf("[ERROR]\n");
        printf("in campo.c: Field_Init()\n");
        printf("Failed to allocate field\n");
        return NULL;
    }

    static int id = 0;

    f->id = id;
    f->img = txr;

    f->anim = Animation_Init();
    Animation_AddPositionAnimation(f->anim, easeOutBack);
    Animation_AddScaleAnimation(f->anim, rect, easeOutBack);

    f->rect = rect;
    f->lastPosition = (Vector2){rect.x, rect.y};
    f->scaleRatio = 1.0f;

    f->hovered = false;

    f->rotation = 0.0f;

    f->cor = WHITE;

    f->scaleType = MAXIMIZEDFIELD;
    f->time = 0.0f;

    f->content = criaLista();
    f->maxItems = maxItems;

    id += 1;

    return f;
}

Rectangle Field_GetRect(Field field){
    return ((FieldStr*)field)->rect;
}

int Field_GetId(Field field){
    return ((FieldStr*)field)->id;
}

bool Field_isHovered(Field field, Vector2 point){
    FieldStr* f = (FieldStr*)field;

    f->hovered = CheckCollisionPointRec(point, f->rect);

    return f->hovered;
}

void Field_SetRotation(Field field, float rotation){
    ((FieldStr*)field)->rotation = rotation;
}

void Field_Move(Field field, Vector2 delta){
    FieldStr* f = (FieldStr*)field;

    f->rect.x += delta.x;
    f->rect.y += delta.y;
}

void Field_MoveTo(Field field, Vector2 finalPoint, float duration){
    FieldStr* f = (FieldStr*)field;

    Vector2 fPoint;
    fPoint.x = finalPoint.x - f->rect.width / 2;
    fPoint.y = finalPoint.y - f->rect.height / 2;

    Vector2 cPos = (Vector2){f->rect.x, f->rect.y};

    Animation_SetPosition(f->anim, cPos);
    Animation_MoveTo(f->anim, fPoint, duration);
}

void Field_SetScaleRatio(Field field, float scaleRatio){
    ((FieldStr*)field)->scaleRatio = scaleRatio;
}

void Field_SetScale(Field field, float scale, float duration){
    FieldStr* f = (FieldStr*)field;

    if(Animation_ScaleIsAnimating(f->anim)) Animation_EndResize(f->anim);
    f->rect = Animation_GetScale(f->anim);

    Animation_Resize(f->anim, scale, duration);
}

void Field_MinimizeContent(Field field, float duration){
    FieldStr* f = (FieldStr*)field;

    if(f->scaleType == MINIMIZEDFIELD) return;

    Field_SetScale(field, f->scaleRatio, duration);

    f->scaleType = MINIMIZEDFIELD;
}

void Field_MedianizeContent(Field field, float duration){
    FieldStr* f = (FieldStr*)field;

    if(f->scaleType == MEDIANIZEDFIELD) return;

    Field_SetScale(field, ((1.0f - f->scaleRatio) * 0.5f) + f->scaleRatio, duration);

    f->scaleType = MEDIANIZEDFIELD;
}

void Field_MaximizeContent(Field field, float duration){
    FieldStr* f = (FieldStr*)field;

    if(f->scaleType == MAXIMIZEDFIELD) return;

    Field_SetScale(field, 1.0f, duration);

    f->scaleType = MAXIMIZEDFIELD;
}

static void Field_UpdatePos(FieldStr* f, float deltaTime){
    Animation_UpdatePosition(f->anim, deltaTime);

    if(!Animation_PositionIsAnimating(f->anim)) return;

    Vector2 pos = Animation_GetPosition(f->anim);
    f->rect.x = pos.x;
    f->rect.y = pos.y;
}

static void Field_UpdateSize(FieldStr* f, float deltaTime){
    Animation_SetRectangle(f->anim, f->rect);
    Animation_UpdateScale(f->anim, deltaTime);

    if(!Animation_ScaleIsAnimating(f->anim)) return;

    f->rect = Animation_GetScale(f->anim);
}

void Field_Update(Field field, float deltaTime){
    FieldStr* f = (FieldStr*)field;

    Field_UpdatePos(f, deltaTime);
    Field_UpdateSize(f, deltaTime);
}

void Field_UpdateLastPosition(Field field){
    FieldStr* f = (FieldStr*)field;

    f->lastPosition = (Vector2){f->rect.x, f->rect.y};
}

void Field_AssignMatrixObject(Field field, Item object, getItemFuncMatrix objSearchFunc, int sizeX, int sizeY){
    FieldStr* f = (FieldStr*)field;

    f->matrix = object;
    f->matrixFunc = objSearchFunc;
    f->matrixSizeX = sizeX;
    f->matrixSizeY = sizeY;
}

Vector2 Field_GetPosition(Field field){
    FieldStr* f = (FieldStr*)field;
    return (Vector2){f->rect.x, f->rect.y};
}

Vector2 Field_GetLastPosition(Field field){
    return ((FieldStr*)field)->lastPosition;
}

float Field_GetRotation(Field field){
    return ((FieldStr*)field)->rotation;
}

void Field_Draw(Field field){
    FieldStr* f = (FieldStr*)field;

    // Textura e' opcional: sem ela, desenha so' o contorno do campo
    if(f->img.id == 0){
        DrawRectangleLinesEx(f->rect, 2.0f, f->cor);
        return;
    }

    Rectangle source = (Rectangle){0, 0, (float)f->img.width, (float)f->img.height};
    Rectangle dest = (Rectangle){
        f->rect.x + f->rect.width / 2.0f,
        f->rect.y + f->rect.height / 2.0f,
        f->rect.width,
        f->rect.height
    };
    Vector2 origin = (Vector2){f->rect.width / 2.0f, f->rect.height / 2.0f};

    DrawTexturePro(f->img, source, dest, origin, f->rotation, f->cor);
}

void Field_DrawFromMatrixObject(Field field){
    FieldStr* f = (FieldStr*)field;

    // Textura e' opcional: sem ela, desenha so' o contorno do campo
    if(f->img.id == 0){
        DrawRectangleLinesEx(f->rect, 2.0f, f->cor);
    }
    else{
        Rectangle source = (Rectangle){0, 0, (float)f->img.width, (float)f->img.height};
        Rectangle dest = (Rectangle){
            f->rect.x + f->rect.width / 2.0f,
            f->rect.y + f->rect.height / 2.0f,
            f->rect.width,
            f->rect.height
        };
        Vector2 origin = (Vector2){f->rect.width / 2.0f, f->rect.height / 2.0f};

        DrawTexturePro(f->img, source, dest, origin, f->rotation, f->cor);
    }
    // ---

    for(int i = 0; i < f->matrixSizeX; i++){
        for(int j = 0; j < f->matrixSizeY; j++){
            Carta c = f->matrixFunc(f->matrix, i, j);

            if(c != NULL){
                int id = getID(c);

                Card card = Card_GetById(id);
                Card_Draw(card);
                printf("\n Drawing card number: %d", Card_GetId(card));
            }
        }
    }
}

Lista Field_free(Field field){
    FieldStr* f = (FieldStr*)field;

    Lista content = f->content;
    f->content = NULL;
    
    Animation_Free(f->anim);
    free(f);

    return content;
}