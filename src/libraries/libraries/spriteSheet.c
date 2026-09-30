#include "spriteSheet.h"

#include <stdio.h>

#include <stdlib.h>
#include <raymath.h>
#include "imageObject.h"
#include <animation.h>
#include <string.h>

#include "utils.h"

#include <hash.h>
Hash spriteAllInstances = NULL;

typedef struct animHash{
    int type;               // type = 1
    int row;
    int amountOfFrames;
    float speed;
} animHash;

typedef struct staticHash{
    int type;               // type = 2
    int row;
    int column;
} staticHash;

typedef struct animatedSpriteStr{
    Animation animation;
    Vector2 currentFrame;

    Rectangle source;
    Rectangle destination;
} animatedSpriteStr;

typedef struct spriteSheetStr{
    int id;
    ImageObject image;

    Hash indexes;
    Animation animation;

    Vector2 currentFrame;

    Vector2 delta;
    Vector2 size;

    char* lastName;

    int typeLoaded;
} spriteSheetStr;

SpriteSheet SpriteSheet_Init(const char* filename, Vector2 delta, Vector2 size, Rectangle dest){
    spriteSheetStr* s = (spriteSheetStr*)malloc(sizeof(spriteSheetStr));

    static int id = 0;
    s->id = id;
    id += 1;

    s->image = Image_Init(filename);
    Image_SetSource(s->image, (Rectangle){0, 0, size.x, size.y});
    s->delta = delta;
    s->size = size;
    Image_SetDestination(s->image, dest);

    s->indexes = criaHash(5, false, 0.75f);
    s->lastName = NULL;

    s->currentFrame = (Vector2){0, 0};

    s->typeLoaded = 0;

    s->animation = Animation_Init();
    Animation_AddFramesAnimation(s->animation, 0, 0, 0);

    createAndInsertInstance(&spriteAllInstances, s->id, s);

    return (SpriteSheet)s;
}

AnimatedSpriteSheetInstance SpriteSheet_CreateAnimatedInstance(SpriteSheet spriteSheet, const char* name, Rectangle destination){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    animatedSpriteStr* an = (animatedSpriteStr*)malloc(sizeof(animatedSpriteStr));
    
    an->animation = Animation_Init();
    Animation_AddFramesAnimation(an->animation, 0, 0, 0);
    
    Item item = getHashValue(s->indexes, name);
    int* temp = (int*)item;

    if(*temp != 1){
        free(an);
        return NULL;
    }

    animHash* animhash = (animHash*)item;

    Animation_SetFrames(an->animation, animhash->amountOfFrames, s->delta.x, animhash->speed);
    
    Vector2 posImage = {0, animhash->row};
    Vector2 finalPos = Vector2Multiply(posImage, s->delta);
    Rectangle source = {finalPos.x, finalPos.y, s->size.x, s->size.y};

    an->source = source;
    an->destination = destination;
    an->currentFrame = finalPos;

    return (AnimatedSpriteSheetInstance)an;
}

// SpriteSheet SpriteSheet_Copy(SpriteSheet spriteSheet){
//     spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

//     const char* filename = Image_GetTextureName(s->image);

//     spriteSheetStr* sCopy = (spriteSheetStr*)SpriteSheet_Init(filename, s->delta, s->size);

//     copyHash();

//     return sCopy;
// }

void SpriteSheet_AddIndex(SpriteSheet spriteSheet, const char* name, int row, int amountOfFrames, float speed){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

    animHash* animhash = (animHash*)malloc(sizeof(animHash));

    animhash->type = 1;
    animhash->amountOfFrames = amountOfFrames;
    animhash->row = row;
    animhash->speed = speed;

    inserirHash(s->indexes, name, animhash);
}

void SpriteSheet_AddStaticIndex(SpriteSheet spriteSheet, const char* name, int row, int column){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

    staticHash* statichash = (staticHash*)malloc(sizeof(staticHash));

    statichash->type = 2;
    statichash->row = row;
    statichash->column = column;

    inserirHash(s->indexes, name, statichash);
}

void SpriteSheet_SetFrame(SpriteSheet spriteSheet, const char* name){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

    if(s->lastName != NULL && strcmp(name, s->lastName) == 0) return;

    if(s->lastName != NULL) free(s->lastName);
    s->lastName = (char*)malloc(strlen(name) + 1);
    strcpy(s->lastName, name);

    Item item = getHashValue(s->indexes, name);
    if(item == NULL) return;

    int* temp = (int*)item;
    Vector2 posImage = {0, 0};

    switch (*temp){
    case 1:
        animHash* animhash = (animHash*)item;
        posImage = (Vector2){0, animhash->row};

        Animation_SetFrames(s->animation, animhash->amountOfFrames, s->delta.x, animhash->speed);
        s->typeLoaded = 1;

        break;
    case 2:
        staticHash* statichash = (staticHash*)item;
        posImage = (Vector2){statichash->column, statichash->row};
        s->typeLoaded = 2;

        break;
    default:
        return;
    }

    Vector2 finalPos = Vector2Multiply(posImage, s->delta);
    Rectangle source = {finalPos.x, finalPos.y, s->size.x, s->size.y};

    Image_SetSource(s->image, source);

    s->currentFrame = finalPos;
}

Vector2 SpriteSheet_GetFramePosition(SpriteSheet spriteSheet, const char* name){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

    if(name == NULL) return (Vector2){0, 0};

    Item item = getHashValue(s->indexes, name);
    if(item == NULL) return (Vector2){0, 0};

    int* temp = (int*)item;
    Vector2 posImage = {0, 0};

    switch (*temp){
    case 1:
        animHash* animhash = (animHash*)item;
        posImage = (Vector2){0, animhash->row};

        break;
    case 2:
        staticHash* statichash = (staticHash*)item;
        posImage = (Vector2){statichash->column, statichash->row};

        break;
    default:
        break;
    }

    return posImage;
}

void SpriteSheet_SetDestination(SpriteSheet spriteSheet, Rectangle destination){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    Image_SetDestination(s->image, destination);
}

Rectangle SpriteSheet_GetDestination(SpriteSheet spriteSheet){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    return Image_GetDestination(s->image);
}

Rectangle SpriteSheet_GetInstanceRec(AnimatedSpriteSheetInstance animatedSprite){
    animatedSpriteStr* an = (animatedSpriteStr*)animatedSprite;
    return an->destination;
}

void SpriteSheet_UpdateAnimation(SpriteSheet spriteSheet, float deltaTime){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

    if(s->typeLoaded != 1) return;

    Animation_UpdateFrames(s->animation, deltaTime);
    s->currentFrame.x = Animation_GetFrameCoord(s->animation);

    Image_SetSource(s->image, (Rectangle){s->currentFrame.x, s->currentFrame.y, s->size.x, s->size.y});
    
    bool animating = Animation_FramesIsAnimating(s->animation);

    if(animating == false) Animation_ReverseFrames(s->animation);
}

void SpriteSheet_UpdateInstance(SpriteSheet spriteSheet, AnimatedSpriteSheetInstance animatedSprite, float deltaTime){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    animatedSpriteStr* an = (animatedSpriteStr*)animatedSprite;

    Animation_UpdateFrames(an->animation, deltaTime);
    an->currentFrame.x = Animation_GetFrameCoord(an->animation);

    an->source = (Rectangle){an->currentFrame.x, an->currentFrame.y, s->size.x, s->size.y};
    
    bool animating = Animation_FramesIsAnimating(an->animation);

    if(animating == false) Animation_ReverseFrames(an->animation);
}

void SpriteSheet_DrawImage(SpriteSheet spriteSheet){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    Image_Draw(s->image);
}

void SpriteSheet_DrawIndex(SpriteSheet spriteSheet, Vector2 coords){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    Vector2 aCoords = Vector2Multiply(coords, s->delta);

    Image_DrawManually(s->image, (Rectangle){aCoords.x, aCoords.y, s->size.x, s->size.y}, Image_GetDestination(s->image));
}

void SpriteSheet_DrawInstance(SpriteSheet spriteSheet, AnimatedSpriteSheetInstance animatedSprite){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    animatedSpriteStr* an = (animatedSpriteStr*)animatedSprite;

    Image_DrawManually(s->image, an->source, an->destination);
}

static void SpriteSheet_FreeInstance(SpriteSheet spriteSheet){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;

    Image_Free(s->image);
    destroiHash(s->indexes, freeReg, NULL);
    free(s);
}

void SpriteSheet_Free(SpriteSheet spriteSheet){
    spriteSheetStr* s = (spriteSheetStr*)spriteSheet;
    removeInstance(spriteAllInstances, s->id);

    SpriteSheet_FreeInstance(spriteSheet);
}

void SpriteSheet_FreeAnimatedInstance(AnimatedSpriteSheetInstance animatedSprite){
    animatedSpriteStr* an = (animatedSpriteStr*)animatedSprite;

    Animation_Free(an->animation);
    free(an);
}

void SpriteSheet_FreeAll(){
    destroiHash(spriteAllInstances, freeExtra, SpriteSheet_FreeInstance);
    spriteAllInstances = NULL;
}