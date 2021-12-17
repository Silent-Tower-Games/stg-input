#pragma once

#include <SDL2/SDL.h>

#define STGINPUT_AXISSTATE_VALUE_MAX 32767
#define STGINPUT_AXISSTATE_VALUE_MIN -32768

/**
 * Axis state object. Holds a signed 16-bit int & a -1.0f to 1.0f float representing the int.
 */
typedef struct STGInput_AxisState
{
    Sint16 value;
    float percentage;
} STGInput_AxisState;

/**
 * Functionally update an axis state. Updates `value` as well as `percentage`.
 *
 * \param state current axis state
 * \param value axis value
 * \return updated axis state
 */
STGInput_AxisState STGInput_AxisState_Update(STGInput_AxisState state, Sint16 value);
