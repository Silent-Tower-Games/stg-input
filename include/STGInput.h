#pragma once

#include "STGInput.h"
#include "ButtonState.h"
#include "GamepadState.h"
#include "KeyboardState.h"
#include "MouseState.h"

/**
 * Input state object. Contains states for keyboard, mouse, & gamepads.
 */
typedef struct STGInput
{
    STGInput_KeyboardState* keyboard;
    STGInput_GamepadStateList* gamepads;
    STGInput_MouseState* mouse;
} STGInput;

/**
 * Create a new input state object.
 *
 * \return input state object
 */
STGInput* STGInput_Create();

/**
 * Act on a given SDL event.
 *
 * \param input input state object
 * \param event SDL event
 */
void STGInput_Event(STGInput* input, SDL_Event event);

/**
 * Performs pre-frame preparation on input states.
 *
 * \param input input state object
 */
void STGInput_PreFrame(STGInput* input);

/**
 * Performs post-frame preparation on input states.
 *
 * \param input input state object
 */
void STGInput_PostFrame(STGInput* input);

/**
 * Destroys all input heap memory & frees the input state object.
 *
 * \param input input state object
 */
void STGInput_Destroy(STGInput* input);
