#ifndef _SLIDER_h_
#define _SLIDER_h_

#include <raylib.h>

typedef void* Slider;

Slider Slider_Init(Rectangle sliderRec, float pointRadius);

void Slider_SetValue(Slider slider, float value);

float Slider_GetValue(Slider slider);

void Slider_Update(Slider slider, Vector2 mousePos, Vector2 mouseDelta);

void Slider_Draw(Slider slider);

void Slider_Free(Slider slider);

#endif