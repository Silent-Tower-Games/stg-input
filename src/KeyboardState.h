#pragma once

#include "ButtonState.h"

#define STGINPUT_KEYBOARDSTATE_KEYCODES_LENGTH 240

extern const SDL_KeyCode STGInput_KeyboardState_Keycodes[STGINPUT_KEYBOARDSTATE_KEYCODES_LENGTH];

typedef struct STGInput_KeyboardState
{
    STGInput_ButtonState button[240];
} STGInput_KeyboardState;

void STGInput_KeyboardState_Event(STGInput_KeyboardState* keyboard, SDL_Event event);

void STGInput_KeyboardState_Update(STGInput_KeyboardState* keyboard);
