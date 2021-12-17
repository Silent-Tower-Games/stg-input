#pragma once

#include "ButtonState.h"

#define STGINPUT_MOUSESTATE_BUTTONS_COUNT 3

typedef enum STGInput_MouseButtons
{
    STGINPUT_MOUSEBUTTONS_LEFTCLICK,
    STGINPUT_MOUSEBUTTONS_MIDDLECLICK,
    STGINPUT_MOUSEBUTTONS_RIGHTCLICK,
} STGInput_MouseButtons;

typedef struct STGInput_MouseState
{
    int X;
    int Y;
    STGInput_ButtonState button[STGINPUT_MOUSESTATE_BUTTONS_COUNT];
} STGInput_MouseState;

extern STGInput_MouseButtons STGInput_MouseButtons_List[STGINPUT_MOUSESTATE_BUTTONS_COUNT];

void STGInput_MouseState_Poll(STGInput_MouseState* mouse);

void STGInput_MouseState_Update(STGInput_MouseState* mouse);

int STGInput_MouseState_ButtonIndex(STGInput_MouseButtons button);

STGInput_ButtonState_Name STGInput_MouseState_Button_GetState(STGInput_MouseState* mouse, STGInput_MouseButtons button);

char STGInput_MouseState_Button_IsDown(STGInput_MouseState* mouse, STGInput_MouseButtons button);

char STGInput_MouseState_Button_IsPressed(STGInput_MouseState* mouse, STGInput_MouseButtons button);

char STGInput_MouseState_Button_IsPressedOrRepeated(STGInput_MouseState* mouse, STGInput_MouseButtons button);

char STGInput_MouseState_Button_IsReleased(STGInput_MouseState* mouse, STGInput_MouseButtons button);
