#pragma once

#include <SDL2/SDL.h>

#define STGINPUT_AXISSTATE_VALUE_MAX 32767
#define STGINPUT_AXISSTATE_VALUE_MIN -32768

typedef struct STGInput_AxisState
{
    Sint16 value;
    float percentage;
} STGInput_AxisState;

STGInput_AxisState STGInput_AxisState_Update(STGInput_AxisState state, Sint16 value);
