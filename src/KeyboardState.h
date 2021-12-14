#pragma once

#include "ButtonState.h"

#define STGINPUT_KEYBOARDSTATE_KEYCODES_LENGTH 240

extern const SDL_KeyCode STGInput_KeyboardState_Keycodes[STGINPUT_KEYBOARDSTATE_KEYCODES_LENGTH];

typedef struct STGInput_KeyboardState
{
    STGInput_ButtonState button[STGINPUT_KEYBOARDSTATE_KEYCODES_LENGTH];
} STGInput_KeyboardState;

void STGInput_KeyboardState_Event(STGInput_KeyboardState* keyboard, SDL_Event event);

void STGInput_KeyboardState_Update(STGInput_KeyboardState* keyboard);

STGInput_ButtonState_Name STGInput_KeyboardState_Button_GetState(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

char STGInput_KeyboardState_Button_IsDown(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

char STGInput_KeyboardState_Button_IsPressed(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

char STGInput_KeyboardState_Button_IsPressedOrRepeated(STGInput_KeyboardState* keyboard, SDL_KeyCode key);
