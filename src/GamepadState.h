#pragma once

#include <SDL2/SDL.h>
#include "AxisState.h"
#include "ButtonState.h"

#define STGINPUT_GAMEPAD_BUTTONS_COUNT 25
#define STGINPUT_GAMEPAD_BUTTONS_COUNT_BUTTONS 15
#define STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES 6
#define STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES_BUTTONS 10

#define STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT 8
#define STGINPUT_GAMEPADSTATE_ID_INVALID -1
#define STGINPUT_GAMEPADSTATE_INDEX_INVALID -1

/**
 * List of gamepad buttons.
 */
typedef enum STGInput_GamepadButtons
{
    // SDL_CONTROLER_BUTTON copies
    STGINPUT_GAMEPADBUTTONS_FACE_DOWN,
    STGINPUT_GAMEPADBUTTONS_FACE_RIGHT,
    STGINPUT_GAMEPADBUTTONS_FACE_LEFT,
    STGINPUT_GAMEPADBUTTONS_FACE_TOP,
    STGINPUT_GAMEPADBUTTONS_BACK,
    STGINPUT_GAMEPADBUTTONS_GUIDE,
    STGINPUT_GAMEPADBUTTONS_START,
    STGINPUT_GAMEPADBUTTONS_STICK_LEFT,
    STGINPUT_GAMEPADBUTTONS_STICK_RIGHT,
    STGINPUT_GAMEPADBUTTONS_SHOULDER_LEFT,
    STGINPUT_GAMEPADBUTTONS_SHOULDER_RIGHT,
    STGINPUT_GAMEPADBUTTONS_DPAD_UP,
    STGINPUT_GAMEPADBUTTONS_DPAD_DOWN,
    STGINPUT_GAMEPADBUTTONS_DPAD_LEFT,
    STGINPUT_GAMEPADBUTTONS_DPAD_RIGHT,
    // Virtual axes buttons
    STGINPUT_GAMEPADBUTTONS_TRIGGER_LEFT,
    STGINPUT_GAMEPADBUTTONS_TRIGGER_RIGHT,
    STGINPUT_GAMEPADBUTTONS_STICK_LEFT_LEFT,
    STGINPUT_GAMEPADBUTTONS_STICK_LEFT_RIGHT,
    STGINPUT_GAMEPADBUTTONS_STICK_LEFT_DOWN,
    STGINPUT_GAMEPADBUTTONS_STICK_LEFT_UP,
    STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_LEFT,
    STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_RIGHT,
    STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_DOWN,
    STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_UP,
} STGInput_GamepadButtons;

/**
 * List of gamepad axes.
 */
typedef enum STGInput_GamepadAxes
{
    STGINPUT_GAMEPADAXES_STICK_LEFT_X,
    STGINPUT_GAMEPADAXES_STICK_LEFT_Y,
    STGINPUT_GAMEPADAXES_STICK_RIGHT_X,
    STGINPUT_GAMEPADAXES_STICK_RIGHT_Y,
    STGINPUT_GAMEPADAXES_TRIGGER_LEFT,
    STGINPUT_GAMEPADAXES_TRIGGER_RIGHT,
} STGInput_GamepadAxes;

/**
 * Gamepad axis mappable options state.
 */
typedef struct STGInput_GamepadAxis_Profile
{
    STGInput_GamepadAxes axis;
    STGInput_GamepadButtons button;
    float rangeBegin;
    float rangeEnd;
} STGInput_GamepadAxis_Profile;

/**
 * Gamepad state object.
 */
typedef struct STGInput_GamepadState STGInput_GamepadState;

/**
 * Gamepad state vector container.
 */
typedef struct STGInput_GamepadStateList STGInput_GamepadStateList;

/**
 * Create a new gamepad state object.
 *
 * \param which ID of the gamepad device
 * \return new gamepad state object
 */
STGInput_GamepadState STGInput_GamepadState_Create(Sint32 which);

/**
 * Destroy all gamepad state heap memory.
 *
 * \param gamepad gamepad state object
 */
void STGInput_GamepadState_Destroy(STGInput_GamepadState* gamepad);

/**
 * Get whether or not a given gamepad state represents an active gamepad.
 *
 * \param gamepad gamepad state object
 * \return 1 for active, 0 otherwise
 */
char STGInput_GamepadState_IsActive(STGInput_GamepadState* gamepad);

/**
 * Get the float value of a given gamepad axis.
 *
 * \param gamepad gamepad state object
 * \param axis button enum value for axis
 * \return between -1.0f and 1.0f
 */
float STGInput_GamepadState_AxisPercentage(STGInput_GamepadState* gamepad, STGInput_GamepadButtons axis);

/**
 * Get the signt 16-bit integer value of a given gamepad axis.
 *
 * \param gamepad gamepad state object
 * \param axis button enum value for axis
 * \return between -32768 and 32767
 */
Sint16 STGInput_GamepadState_AxisValue(STGInput_GamepadState* gamepad, STGInput_GamepadButtons axis);

/**
 * Get the state object of a given gamepad button.
 *
 * \param gamepad gamepad state object
 * \param button button enum value
 * \return button state object
 */
STGInput_ButtonState_Name STGInput_GamepadState_Button_GetState(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

/**
 * Get whether the button is down or not.
 * Returns true for PRESSED, DOWN, etc.
 *
 * \param gamepad gamepad state object
 * \param button button enum value
 * \return 1 for down, 0 for otherwise
 */
char STGInput_GamepadState_Button_IsDown(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

/**
 * Get whether or not the button is newly pressed this frame.
 *
 * \param gamepad gamepad state object
 * \param button button enum value
 * \return 1 for pressed, 0 otherwise
 */
char STGInput_GamepadState_Button_IsPressed(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

/**
 * Get whether or not the button is pressed or repeat-pressed.
 * Repeat-pressed is never true for a gamepad.
 *
 * \param gamepad gamepad state object
 * \param button button enum value
 * \return 1 for pressed / repeat-pressed, 0 otherwise
 */
char STGInput_GamepadState_Button_IsPressedOrRepeated(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

/**
 * Get whether or not the button is newly released this frame.
 *
 * \param gamepad gamepad state object
 * \param button button enum value
 * \return 1 for released, 0 otherwise
 */
char STGInput_GamepadState_Button_IsReleased(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

/**
 * Create a new gamepad state vector container. Pre-allocateds 8 slots, will allocate more if needed.
 *
 * \return new gamepad state vector container
 */
STGInput_GamepadStateList* STGInput_GamepadStateList_Create();

/**
 * Destroy all gamepad state & vector container heap memory, and free the list object.
 *
 * \param list gamepad state vector container
 */
void STGInput_GamepadStateList_Destroy(STGInput_GamepadStateList* list);

/**
 * Get a gamepad by its player index. E.g. Player One is 0, Player Two is 1, etc.
 *
 * \param list gamepad state vector container
 * \param index player index
 * \return gamepad state, if exists; NULL otherwise
 */
STGInput_GamepadState* STGInput_GamepadStateList_FindByIndex(STGInput_GamepadStateList* list, int index);

/**
 * Act on a given SDL Event.
 *
 * \param list gamepad state vector container
 * \param event SDL event
 */
void STGInput_GamepadStateList_Event(STGInput_GamepadStateList* list, SDL_Event event);

/**
 * Update button state objects for all gamepad axes. Should be called once per frame, after acting on SDL events.
 *
 * \param list gamepad state vector container
 */
void STGInput_GamepadStateList_SetAxesButtons(STGInput_GamepadStateList* list);

/**
 * Update button states for all gamepad axes.
 * Will change PRESSED to DOWN, RELEASED to UP, etc.
 *
 * \param list gamepad state vector container
 */
void STGInput_GamepadStateList_Update(STGInput_GamepadStateList* list);
