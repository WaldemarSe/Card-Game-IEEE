#ifndef _AUDIO_h_
#define _AUDIO_h_

#include <raylib.h>
#include <slider.h>

typedef void* AudioSlider;

#define MAX_RAW_SOUNDS 10
#define MAX_STREAM_SOUNDS 4

AudioSlider Audio_AssignSlider(Music audio, Slider slider);

void Audio_Update(AudioSlider audioSlider);

void Audio_SliderFree(AudioSlider audioSlider);

#endif