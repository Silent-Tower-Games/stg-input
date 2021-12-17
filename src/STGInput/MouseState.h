#pragma once

#include "ButtonState.h"

#define STGINPUT_MOUSESTATE_BUTTONS_COUNT 3

/**
 * List of supported mouse buttons.
 */
typedef enum STGInput_MouseButtons
{
    STGINPUT_MOUSEBUTTONS_LEFTCLICK,
    STGINPUT_MOUSEBUTTONS_MIDDLECLICK,
    STGINPUT_MOUSEBUTTONS_RIGHTCLICK,
} STGInput_MouseButtons;

/**
 * Mouse position state object.
 */
typedef struct STGInput_MousePosition {
    int X;
    int Y;
} STGInput_MousePosition;

/**
 * Mouse state object.
 */
typedef struct STGInput_MouseState STGInput_MouseState;

/**
 * Create a new mouse state object.
 *
 * \return mouse state object
 */
STGInput_MouseState* STGInput_MouseState_Create();

/**
 * Update a mouse state object with the current mouse state.
 *
 * \param mouse state object
 */
void STGInput_MouseState_Poll(STGInput_MouseState* mouse);

/**
 * Update a mouse state object's button states.
 * Will change PRESSED to DOWN, RELEASED to UP, etc.
 *
 * \param mouse state object
 */
void STGInput_MouseState_Update(STGInput_MouseState* mouse);

/**
 * Get the state object of a given mouse button.
 *
 * \param mouse mouse state object
 * \param button button enum value
 * \return button state object
 */
STGInput_ButtonState_Name STGInput_MouseState_Button_GetState(STGInput_MouseState* mouse, STGInput_MouseButtons button);

/**
 * Get whether the button is down or not.
 * Returns true for PRESSED, DOWN, etc.
 *
 * \param mouse mouse state object
 * \param button button enum value
 * \return 1 for down, 0 for otherwise
 */
char STGInput_MouseState_Button_IsDown(STGInput_MouseState* mouse, STGInput_MouseButtons button);

/**
 * Get whether or not the button is newly pressed this frame.
 *
 * \param mouse mouse state object
 * \param button button enum value
 * \return 1 for pressed, 0 otherwise
 */
char STGInput_MouseState_Button_IsPressed(STGInput_MouseState* mouse, STGInput_MouseButtons button);

/**
 * Get whether or not the button is pressed or repeat-pressed.
 * Repeat-pressed is never true for a gamepad.
 *
 * \param mouse mouse state object
 * \param button button enum value
 * \return 1 for pressed / repeat-pressed, 0 otherwise
 */
char STGInput_MouseState_Button_IsPressedOrRepeated(STGInput_MouseState* mouse, STGInput_MouseButtons button);

/**
 * Get whether or not the button is newly released this frame.
 *
 * \param mouse mouse state object
 * \param button button enum value
 * \return 1 for released, 0 otherwise
 */
char STGInput_MouseState_Button_IsReleased(STGInput_MouseState* mouse, STGInput_MouseButtons button);

/**
 * Get the mouse position state object from a mouse state object.
 *
 * \param mouse mouse state object
 */
STGInput_MousePosition STGInput_MouseState_Position(STGInput_MouseState* mouse);
