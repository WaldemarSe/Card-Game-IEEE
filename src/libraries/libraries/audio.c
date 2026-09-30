#include <audio.h>

#include <stdlib.h>

typedef struct AudioSliderStr{
    Music audio;
    Slider slider;
} AudioSliderStr;

AudioSlider Audio_AssignSlider(Music audio, Slider slider){
    AudioSliderStr* a = (AudioSliderStr*)malloc(sizeof(AudioSliderStr));

    a->audio = audio;
    a->slider = slider;

    return (AudioSlider)a;
}

void Audio_Update(AudioSlider audioSlider){
    AudioSliderStr* a = (AudioSliderStr*)audioSlider;

    float volume = Slider_GetValue(a->slider);
    SetMusicVolume(a->audio, volume);
}

void Audio_SliderFree(AudioSlider audioSlider){
    free(audioSlider);
}