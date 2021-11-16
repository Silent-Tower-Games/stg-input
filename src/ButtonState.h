#pragma once

typedef enum STGInput_ButtonState_Name
{
    STGINPUT_BUTTONSTATE_NAME_INVALID = -1,
    STGINPUT_BUTTONSTATE_NAME_UP,
    STGINPUT_BUTTONSTATE_NAME_DOWN,
    STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT,
    STGINPUT_BUTTONSTATE_NAME_PRESSED,
    STGINPUT_BUTTONSTATE_NAME_RELEASED,
    STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED,
    STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK,
    STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED,
} STGInput_ButtonState_Name;

typedef struct STGInput_ButtonState
{
    float value;
    STGInput_ButtonState_Name state;
    int lastPressed;
} STGInput_ButtonState;

int STGInput_ButtonState_Name_IsDown(STGInput_ButtonState_Name buttonState);

int STGInput_ButtonState_Name_IsPressed(STGInput_ButtonState_Name buttonState);

char* STGInput_ButtonState_Name_ToString(STGInput_ButtonState_Name buttonState);
