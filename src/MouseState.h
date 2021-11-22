#pragma once

typedef enum STGInput_MouseButtons
{
    MOUSEBUTTONS_LEFTCLICK,
    MOUSEBUTTONS_MIDDLECLICK,
    MOUSEBUTTONS_RIGHTCLICK,
} STGInput_MouseButtons;

typedef struct STGInput_MouseState
{
    int X;
    int Y;
} STGInput_MouseState;

void STGInput_MouseState_Update(STGInput_MouseState* mouseState);
