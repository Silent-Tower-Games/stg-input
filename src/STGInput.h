#pragma once

#include "STGInput.h"
#include "GamepadState.h"
#include "KeyboardState.h"
#include "MouseState.h"

typedef struct STGInput
{
    STGInput_KeyboardState keyboard;
} STGInput;

STGInput* STGInput_Create();
