#include "Animation.h"

#include <stdio.h>
#include <stdlib.h>
#include <raymath.h>

#include <hash.h>
Hash animationAllInstances = NULL;

typedef struct AnimResources{
    float elapsed;
    bool animating;
    float duration;
} AnimResources;

typedef struct PositionAnimation{
    AnimResources resources;

    interpolationFunction interFunc;

    Vector2 start;
    Vector2 current; // (current position)
    Vector2 end;
} PositionAnimation;

typedef struct ScaleAnimation{
    AnimResources resources;

    interpolationFunction interFunc;

    Rectangle originalRec;  // (original size)
    Rectangle rectangle;    // (current size)

    float start;
    float current;
    float end;
} ScaleAnimation;

typedef struct FramesAnimation{
    bool animating;

    float frameDelta;
    float frameCoord;

    bool reversed;
    int currentFrame;
    int amountOfFrames;
    float framesCounter;

    float framesSpeed;
} FramesAnimation;

typedef struct AnimationStr{
    int id;

    PositionAnimation* position;
    ScaleAnimation* scale;
    FramesAnimation* frames;
} AnimationStr;

static AnimResources Animation_ResourcesInit(){
    return (AnimResources){0, false, 0.0f};
}

Animation Animation_Init(){
    AnimationStr* anim = (AnimationStr*)malloc(sizeof(AnimationStr));
    
    static int id = 0;
    anim->id = id;
    id += 1;

    anim->position = NULL;
    anim->scale = NULL;
    anim->frames = NULL;

    createAndInsertInstance(&animationAllInstances, anim->id, anim);

    return (Animation)anim;
}

static PositionAnimation* Animation_PositionInit(interpolationFunction interFunc){
    PositionAnimation* posAnim = (PositionAnimation*)malloc(sizeof(PositionAnimation));
    
    posAnim->resources = Animation_ResourcesInit();
    posAnim->start = posAnim->current = posAnim->end = (Vector2){0, 0};
    posAnim->interFunc = interFunc;

    return posAnim;
}

static ScaleAnimation* Animation_ScaleInit(Rectangle rectangle, interpolationFunction interFunc){
    ScaleAnimation* scaleAnim = (ScaleAnimation*)malloc(sizeof(ScaleAnimation));

    scaleAnim->resources = Animation_ResourcesInit();
    scaleAnim->start = 1.0f;
    scaleAnim->current = 1.0f;
    scaleAnim->end = 1.0f;

    scaleAnim->originalRec = rectangle;
    scaleAnim->rectangle = rectangle;

    scaleAnim->interFunc = interFunc;

    return scaleAnim;
}

static FramesAnimation* Animation_FramesInit(int amountOfFrames, float framesSpeed, float frameDelta){
    FramesAnimation* framesAnim = (FramesAnimation*)malloc(sizeof(FramesAnimation));

    framesAnim->animating = false;
    framesAnim->frameDelta = frameDelta;
    framesAnim->frameCoord = 0.0f;
    framesAnim->reversed = false;
    framesAnim->currentFrame = 0;
    framesAnim->amountOfFrames = amountOfFrames;
    framesAnim->framesCounter = 0;
    framesAnim->framesSpeed = framesSpeed;

    return framesAnim;
}

void Animation_AddPositionAnimation(Animation animation, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;

    anim->position = Animation_PositionInit(interFunc);
}

void Animation_AddScaleAnimation(Animation animation, Rectangle rectangle, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;

    anim->scale = Animation_ScaleInit(rectangle, interFunc);
}

void Animation_AddFramesAnimation(Animation animation, int amountOfFrames, float framesSpeed, float frameDelta){
    AnimationStr* anim = (AnimationStr*)animation;

    anim->frames = Animation_FramesInit(amountOfFrames, framesSpeed, frameDelta);
}

void Animation_MoveTo(Animation animation, Vector2 finalPoint, float duration){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    animPos->end = finalPoint;

    animPos->resources.duration = duration;
    animPos->resources.elapsed = 0;
    animPos->resources.animating = true;
}

void Animation_UpdatePosition(Animation animation, float deltaTime){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    Vector2 current = animPos->end;

    if(animPos->resources.animating == false) return;

    animPos->resources.elapsed += deltaTime;

    float progress = animPos->resources.elapsed / animPos->resources.duration;

    if(progress >= 1.0f){
        progress = 1.0f;
        animPos->resources.animating = false;
    }
    
    float eased = animPos->interFunc(progress);

    current.x = Lerp(animPos->start.x, animPos->end.x, eased);
    current.y = Lerp(animPos->start.y, animPos->end.y, eased);

    animPos->current = current;
}

bool Animation_PositionIsAnimating(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return false;

    return animPos->resources.animating;
}

void Animation_Resize(Animation animation, float scaleTo, float duration){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    animScale->start = 1.0f;

    float targetWidth = animScale->originalRec.width * scaleTo;
    float targetScale = targetWidth / animScale->rectangle.width;

    animScale->end = targetScale;
    animScale->current = 1.0f;

    animScale->resources.duration = duration;
    animScale->resources.elapsed = 0.0f;
    animScale->resources.animating = true;
}

void Animation_UpdateScale(Animation animation, float deltaTime){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    Rectangle recItem = animScale->rectangle;

    if(animScale->resources.animating == false) return;

    animScale->resources.elapsed += deltaTime;

    float progress = animScale->resources.elapsed / animScale->resources.duration;

    if(progress >= 1.0f){
        animScale->resources.animating = false;
    }

    float eased = animScale->interFunc(progress);

    float prevScale = animScale->current;
    float newScale = Lerp(animScale->start, animScale->end, eased);
    
    animScale->current = newScale;

    Vector2 center = getRectCenter(recItem);

    float baseWidth = recItem.width / prevScale;
    float baseHeight = recItem.height / prevScale;

    recItem.width = baseWidth * newScale;
    recItem.height = baseHeight * newScale;

    recItem.x = center.x - recItem.width / 2.0f;
    recItem.y = center.y - recItem.height / 2.0f;

    animScale->rectangle = recItem;
}

bool Animation_ScaleIsAnimating(Animation animation){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->scale == NULL) return false;

    return a->scale->resources.animating;
}

void Animation_EndResize(Animation animation){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->scale == NULL || a->scale->resources.animating == false) return;

    ScaleAnimation* animScale = a->scale;

    Rectangle recItem = animScale->rectangle;

    animScale->resources.animating = false;
    animScale->resources.elapsed = 0.0f;

    float prevScale = animScale->current;
    float newScale = animScale->end;
    
    animScale->current = newScale;

    Vector2 center = getRectCenter(recItem);

    float baseWidth = recItem.width / prevScale;
    float baseHeight = recItem.height / prevScale;

    recItem.width = baseWidth * newScale;
    recItem.height = baseHeight * newScale;

    recItem.x = center.x - recItem.width / 2.0f;
    recItem.y = center.y - recItem.height / 2.0f;

    animScale->rectangle = recItem;
}

void Animation_UpdateFrames(Animation animation, float deltaTime){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->frames == NULL) return;
    FramesAnimation* frames = a->frames;

    frames->framesCounter += deltaTime;

    // Vai pro pro'ximo frame
    if((frames->framesCounter >= frames->framesSpeed) && frames->animating){
        int direction = (frames->reversed ? -1 : 1);

        frames->framesCounter = 0.0f;
        frames->currentFrame += direction;

        if(frames->currentFrame > frames->amountOfFrames - 1){
            frames->animating = false;
            frames->currentFrame = frames->amountOfFrames - 2;
        }
        if(frames->currentFrame < 0){
            frames->animating = false;
            frames->currentFrame = 1;
        }

        if(frames->currentFrame != 0) frames->frameCoord = (float)frames->currentFrame * frames->frameDelta;
        else frames->frameCoord = 0.0f;
    }
}

void Animation_ReverseFrames(Animation animation){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->frames == NULL) return;
    FramesAnimation* frames = a->frames;

    frames->reversed = !frames->reversed;
    frames->framesCounter = 0.0f;
    frames->currentFrame = (frames->reversed ? (frames->amountOfFrames - 2) : (1));
    frames->frameCoord = frames->frameDelta * frames->currentFrame;

    frames->animating = true;
}

bool Animation_FramesIsAnimating(Animation animation){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->frames == NULL) return false;
    FramesAnimation* frames = a->frames;

    return frames->animating;
}

void Animation_ResetFrames(Animation animation){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->frames == NULL) return;
    FramesAnimation* frames = a->frames;

    frames->reversed = false;
    frames->framesCounter = 0.0f;
    frames->currentFrame = 0;
    frames->frameCoord = 0;

    frames->animating = true;
}

void Animation_SetFrames(Animation animation, int amountOfFrames, float frameDelta, float framesSpeed){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->frames == NULL) return;
    FramesAnimation* frames = a->frames;

    frames->amountOfFrames = amountOfFrames;
    frames->frameDelta = frameDelta;
    frames->framesSpeed = framesSpeed;

    frames->animating = true;
    frames->reversed = false;
    frames->frameCoord = 0.0f;
    frames->framesCounter = 0.0f;
    frames->currentFrame = 0;
}

float Animation_GetFrameCoord(Animation animation){
    AnimationStr* a = (AnimationStr*)animation;

    if(a->frames == NULL) return 0.0f;
    FramesAnimation* frames = a->frames;

    return frames->frameCoord;
}

void Animation_UpdateAll(Animation animation, float deltaTime){
    Animation_UpdatePosition(animation, deltaTime);
    Animation_UpdateScale(animation, deltaTime);
    Animation_UpdateFrames(animation, deltaTime);
}

void Animation_SetPosition(Animation animation, Vector2 position){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    animPos->start = position;
    animPos->current = position;
}

Vector2 Animation_GetPosition(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    return (animPos == NULL ? (Vector2){0, 0} : animPos->current);
}

void Animation_SetRectangle(Animation animation, Rectangle rectangle){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    animScale->rectangle = rectangle;
}

Rectangle Animation_GetScale(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    return (animScale == NULL ? (Rectangle){0, 0, 0, 0} : animScale->rectangle);
}

void Animation_SetPositionFunction(Animation animation, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;
    PositionAnimation* animPos = anim->position;

    if(animPos == NULL) return;

    animPos->interFunc = interFunc;
}

void Animation_SetScaleFunction(Animation animation, interpolationFunction interFunc){
    AnimationStr* anim = (AnimationStr*)animation;
    ScaleAnimation* animScale = anim->scale;

    if(animScale == NULL) return;

    animScale->interFunc = interFunc;
}

static void animFreeScale(ScaleAnimation* scale){
    free(scale);
}

static void animFreeFrames(FramesAnimation* frames){
    free(frames);
}

static void animFreePos(PositionAnimation* pos){
    free(pos);
}

static void Animation_FreeInstance(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;

    if(anim->scale != NULL) animFreeScale(anim->scale);
    if(anim->frames != NULL) animFreeFrames(anim->frames);
    if(anim->position != NULL) animFreePos(anim->position);

    free(anim);
}

void Animation_Free(Animation animation){
    AnimationStr* anim = (AnimationStr*)animation;
    removeInstance(animationAllInstances, anim->id);
    
    Animation_FreeInstance(animation);
}

void Animation_FreeAll(){
    destroiHash(animationAllInstances, freeExtra, Animation_FreeInstance);
    animationAllInstances = NULL;
}