#pragma once

#include "STGInput.h"
#include "ButtonState.h"
#include "GamepadState.h"
#include "KeyboardState.h"
#include "MouseState.h"

typedef struct STGInput
{
    STGInput_KeyboardState* keyboard;
    STGInput_GamepadStateList* gamepads;
    STGInput_MouseState* mouse;
} STGInput;

STGInput* STGInput_Create();

void STGInput_Event(STGInput* input, SDL_Event event);

void STGInput_PreFrame(STGInput* input);

void STGInput_PostFrame(STGInput* input);

void STGInput_Destroy(STGInput* input);
