#include "button.h"

#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct ButtonStr{
    int id;

    Vector2 position;
    float width, height;
    
    char text[MAX_STRSIZE];
    
    int fontsize;
    int borda;

    bool hovering;
    bool pressed;

    Color textFill;
    Color border;
    Color textHover;
    Color fillHover;
} ButtonStr;

Button Button_Init(const char* text, int fontsize, Vector2 position, Color textFill, Color border, Color textHover, Color fillHover){
    ButtonStr* btn = (ButtonStr*)malloc(sizeof(ButtonStr));

    static int id = 0;
    btn->id = id;
    id += 1;

    btn->position = position;

    btn->width = 0.0f;
    btn->height = 0.0f;

    btn->fontsize = fontsize;
    btn->borda = 3;

    btn->hovering = false;
    btn->pressed = false;

    btn->textFill = textFill;
    btn->border = border;
    btn->textHover = textHover;
    btn->fillHover = fillHover;

    strncpy(btn->text, text, MAX_STRSIZE);

    Button_FitSizeToTextsize((Button)btn);

    return (Button)btn;
}

void Button_Scale(Button button, float scale){
    ButtonStr* btn = (ButtonStr*)button;

    btn->width *= scale;
    btn->height *= scale;
    btn->borda *= scale;
}

void Button_FitSizeToTextsize(Button button){
    ButtonStr* btn = (ButtonStr*)button;
    
    btn->width = MeasureText(btn->text, btn->fontsize) * 1.1f;
    btn->height = btn->fontsize * 1.1f;

    btn->borda = btn->height * 0.1f;
}

void Button_FitTextsizeToSize(Button button){
    ButtonStr* btn = (ButtonStr*)button;

    btn->fontsize = btn->height * 0.9f;
}

void Button_SetPosition(Button button, Vector2 position){
    ButtonStr* btn = (ButtonStr*)button;
    btn->position = position;
}

void Button_SetRec(Button button, Rectangle rec){
    ButtonStr* btn = (ButtonStr*)button;

    btn->position.x = rec.x;
    btn->position.y = rec.y;
    btn->width = rec.width;
    btn->height = rec.height;
}

Rectangle Button_GetRec(Button button){
    ButtonStr* btn = (ButtonStr*)button;

    return (Rectangle){btn->position.x, btn->position.y, btn->width, btn->height};
}

bool Button_isHovering(Button button, Vector2 point){
    ButtonStr* btn = (ButtonStr*)button;

    Rectangle rect ={ btn->position.x, btn->position.y, btn->width, btn->height };
    btn->hovering = CheckCollisionPointRec(point, rect);

    return btn->hovering;
}

bool Button_isPressedByMouse(Button button){
    Vector2 mousePos = GetMousePosition();
    bool hoveringButton = Button_isHovering(button, mousePos);

    return hoveringButton && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Button_Draw(Button button){
    ButtonStr* btn = (ButtonStr*)button;

    Rectangle rect = { btn->position.x, btn->position.y, btn->width, btn->height };
    Vector2 mousePos = GetMousePosition();

    if(!Button_isHovering(button, mousePos)){
        DrawRectangleLinesEx(rect, btn->borda, btn->border);
        DrawText(btn->text, btn->position.x + btn->width / 2 - MeasureText(btn->text, btn->fontsize) / 2, btn->position.y + btn->height / 2 - btn->fontsize / 2, btn->fontsize, btn->textFill);
    } else{
        DrawRectangleRec(rect, btn->fillHover);
        DrawText(btn->text, btn->position.x + btn->width / 2 - MeasureText(btn->text, btn->fontsize) / 2, btn->position.y + btn->height / 2 - btn->fontsize / 2, btn->fontsize, btn->textHover);
    }
}

void Button_Free(Button button){
    ButtonStr* btn = (ButtonStr*)button;
    free(btn);
}