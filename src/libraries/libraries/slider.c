#include <slider.h>

#include <math.h>

#include <stdlib.h>
#include <utils.h>

#include <stdio.h>

typedef struct SliderStr{
    Rectangle sliderRec;

    Vector2 pointPos;
    float pointRadius;

    float currentValue;
    bool isGrabbing;
} SliderStr;

Slider Slider_Init(Rectangle sliderRec, float pointRadius){
    SliderStr* s = (SliderStr*)malloc(sizeof(SliderStr));

    s->sliderRec = sliderRec;
    
    s->pointPos.x = sliderRec.x + sliderRec.width;
    s->pointPos.y = sliderRec.y + sliderRec.height / 2.0f;
    s->pointRadius = pointRadius;
    
    s->currentValue = 1.0f;
    s->isGrabbing = false;

    return (Slider)s;
}

void Slider_SetValue(Slider slider, float value){
    ((SliderStr*)slider)->currentValue = value;
}

float Slider_GetValue(Slider slider){
    return ((SliderStr*)slider)->currentValue;
}

void Slider_Update(Slider slider, Vector2 mousePos, Vector2 mouseDelta){
    SliderStr* s = (SliderStr*)slider;

    if(CheckCollisionPointCircle(mousePos, s->pointPos, s->pointRadius) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        s->isGrabbing = true;
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        s->isGrabbing = false;
    }

    if(s->isGrabbing){
        s->pointPos.x = fclamp(mousePos.x, s->sliderRec.x, s->sliderRec.x + s->sliderRec.width);
        s->currentValue = (s->pointPos.x - s->sliderRec.x) / s->sliderRec.width;
    }
}

void Slider_Draw(Slider slider){
    SliderStr* s = (SliderStr*)slider;

    DrawRectangleRec(s->sliderRec, GRAY);
    DrawCircleV(s->pointPos, s->pointRadius, WHITE);
}

void Slider_Free(Slider slider){
    free(slider);
}