#pragma once

#define STGINPUT_BUTTONSTATE_EVENT_DOWN 1
#define STGINPUT_BUTTONSTATE_EVENT_UP 0
#define STGINPUT_BUTTONSTATE_EVENT_REPEAT 1
#define STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT 0

typedef enum STGInput_ButtonState_Name
{
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

STGInput_ButtonState STGInput_ButtonState_Event(
    STGInput_ButtonState buttonState,
    char down,
    char repeat
);

STGInput_ButtonState STGInput_ButtonState_Update(STGInput_ButtonState buttonState);

char STGInput_ButtonState_Name_IsDown(STGInput_ButtonState_Name buttonState);

char STGInput_ButtonState_Name_IsPressed(STGInput_ButtonState_Name buttonState);

char STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_ButtonState_Name buttonState);

char STGInput_ButtonState_Name_IsReleased(STGInput_ButtonState_Name buttonState);

char* STGInput_ButtonState_Name_ToString(STGInput_ButtonState_Name buttonState);
