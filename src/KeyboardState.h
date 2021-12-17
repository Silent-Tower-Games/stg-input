#pragma once

#include "ButtonState.h"

#define STGINPUT_KEYBOARDSTATE_KEYCODES_LENGTH 240

/**
 * Keyboard state object.
 */
typedef struct STGInput_KeyboardState STGInput_KeyboardState;

/**
 * Create a new keyboard state object.
 *
 * \return keyboard state object
 */
STGInput_KeyboardState* STGInput_KeyboardState_Create();

/**
 * Act on an SDL event with a keyboard state object.
 *
 * \param keyboard keyboard state object
 * \param event SDL event
 */
void STGInput_KeyboardState_Event(STGInput_KeyboardState* keyboard, SDL_Event event);

/**
 * Update a keyboard state object's button states.
 * Will change PRESSED to DOWN, RELEASED to UP, etc.
 *
 * \param keyboard keyboard state object
 */
void STGInput_KeyboardState_Update(STGInput_KeyboardState* keyboard);

/**
 * Get the state object of a given keyboard button.
 *
 * \param keyboard keyboard state object
 * \param button button enum value
 * \return button state object
 */
STGInput_ButtonState_Name STGInput_KeyboardState_Button_GetState(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

/**
 * Get whether the button is down or not.
 * Returns true for PRESSED, DOWN, etc.
 *
 * \param keyboard keyboard state object
 * \param button button enum value
 * \return 1 for down, 0 for otherwise
 */
char STGInput_KeyboardState_Button_IsDown(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

/**
 * Get whether or not the button is newly pressed this frame.
 *
 * \param keyboard keyboard state object
 * \param button button enum value
 * \return 1 for pressed, 0 otherwise
 */
char STGInput_KeyboardState_Button_IsPressed(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

/**
 * Get whether or not the button is pressed or repeat-pressed.
 * Repeat-pressed is never true for a gamepad.
 *
 * \param keyboard keyboard state object
 * \param button button enum value
 * \return 1 for pressed / repeat-pressed, 0 otherwise
 */
char STGInput_KeyboardState_Button_IsPressedOrRepeated(STGInput_KeyboardState* keyboard, SDL_KeyCode key);

/**
 * Get whether or not the button is newly released this frame.
 *
 * \param keyboard keyboard state object
 * \param button button enum value
 * \return 1 for released, 0 otherwise
 */
char STGInput_KeyboardState_Button_IsReleased(STGInput_KeyboardState* keyboard, SDL_KeyCode key);
