#include "animatedButton.h"

#include <stdlib.h>

#include <button.h>
#include <animation.h>

typedef struct animatedButtonStr{
    Button button;
    Animation animation;

    Rectangle initialRec;
    bool downAnim;
    bool pressed;

    float resizeRatio;
    float speedAnim;
} animatedButtonStr;

AnimatedButton AnimatedButton_Init(const char* text, int fontsize, Vector2 position, Color textFill, Color border, Color textHover, Color fillHover, float resizeRatio, float speedAnim){
    animatedButtonStr* animBtn = (animatedButtonStr*)malloc(sizeof(animatedButtonStr));

    animBtn->button = Button_Init(text, fontsize, position, textFill, border, textHover, fillHover);

    animBtn->initialRec = Button_GetRec(animBtn->button);

    animBtn->animation = Animation_Init();
    Animation_AddScaleAnimation(animBtn->animation, animBtn->initialRec, easeOutBack);

    animBtn->downAnim = false;
    animBtn->pressed = false;

    animBtn->resizeRatio = resizeRatio;
    animBtn->speedAnim = speedAnim;

    return (AnimatedButton)animBtn;
}

bool AnimatedButton_isPressedByMouse(AnimatedButton button){
    animatedButtonStr* animBtn = (animatedButtonStr*)button;

    bool pressed = Button_isPressedByMouse(animBtn->button);
    
    if(pressed == true) animBtn->pressed = true;

    return pressed;
}

bool AnimatedButton_isReleasedByMouse(AnimatedButton button){
    animatedButtonStr* animBtn = (animatedButtonStr*)button;

    Vector2 mousePos = GetMousePosition();

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && Button_isHovering(animBtn->button, mousePos) && animBtn->pressed == true){
        animBtn->pressed = false;
        return true;
    }
    if(!Button_isHovering(animBtn->button, mousePos) && animBtn->pressed == true){
        animBtn->pressed = false;
        return true;
    }

    return false;
}

void AnimatedButton_PlayAnimation(AnimatedButton button){
    animatedButtonStr* animBtn = (animatedButtonStr*)button;

    animBtn->downAnim = !animBtn->downAnim;
    float resize = 1.0f;

    if(animBtn->downAnim) resize = animBtn->resizeRatio;
    else resize = 1/animBtn->resizeRatio;

    Animation_EndResize(animBtn->animation);
    Animation_Resize(animBtn->animation, resize, animBtn->speedAnim);
}

void AnimatedButton_Feedback(AnimatedButton button){
    if(AnimatedButton_isPressedByMouse(button) || AnimatedButton_isReleasedByMouse(button)) AnimatedButton_PlayAnimation(button);
}

void AnimatedButton_Update(AnimatedButton button, float deltaTime){
    animatedButtonStr* animBtn = (animatedButtonStr*)button;

    if(!Animation_ScaleIsAnimating(animBtn->animation)) return;

    Animation_UpdateScale(animBtn->animation, deltaTime);

    Rectangle newRec = Animation_GetScale(animBtn->animation);

    Button_SetRec(animBtn->button, newRec);
    Button_FitTextsizeToSize(animBtn->button);
}

void AnimatedButton_Draw(AnimatedButton button){
    animatedButtonStr* animBtn = (animatedButtonStr*)button;

    Button_Draw(animBtn->button);
}

void AnimatedButton_Free(AnimatedButton button){
    animatedButtonStr* animBtn = (animatedButtonStr*)button;

    Button_Free(animBtn->button);
    Animation_Free(animBtn->animation);

    free(animBtn);
}