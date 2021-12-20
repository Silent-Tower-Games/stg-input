#pragma once

#define STGINPUT_BUTTONSTATE_EVENT_DOWN 1
#define STGINPUT_BUTTONSTATE_EVENT_UP 0
#define STGINPUT_BUTTONSTATE_EVENT_REPEAT 1
#define STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT 0

/**
 * List of possible button press states.
 */
typedef enum STGInput_ButtonState_Name
{
    STGINPUT_BUTTONSTATE_NAME_UP,
    STGINPUT_BUTTONSTATE_NAME_DOWN,
    STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT,
    STGINPUT_BUTTONSTATE_NAME_PRESSED,
    STGINPUT_BUTTONSTATE_NAME_RELEASED,
    STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED,
    STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK,
    STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED,
} STGInput_ButtonState_Name;

/**
 * Button state object.
 */
typedef struct STGInput_ButtonState
{
    float value;
    STGInput_ButtonState_Name state;
    int lastPressed;
} STGInput_ButtonState;

/**
 * Functionally update a button state object based on an event.
 *
 * \param buttonState current button state
 * \param down whether or not the button is currently "down" (pressed)
 * \param repeat whether or not this press is a "repeat" (e.g. when holding down a keyboard character key)
 * \return updated button state
 */
STGInput_ButtonState STGInput_ButtonState_Event(
    STGInput_ButtonState buttonState,
    char down,
    char repeat
);

/**
 * Functionally update a button state object based on passage of time.
 * Will change PRESSED to DOWN, RELEASED to UP, etc.
 *
 * \param buttonState current button state
 * \return updated button state
 */
STGInput_ButtonState STGInput_ButtonState_Update(STGInput_ButtonState buttonState);

/**
 * Get whether or not the button is down.
 * Returns true for PRESSED, DOWN, etc.
 *
 * \param buttonState current button state
 * \return 1 for down, 0 otherwise
 */
char STGInput_ButtonState_Name_IsDown(STGInput_ButtonState_Name buttonState);

/**
 * Get whether or not the button is newly pressed this frame.
 *
 * \param buttonState current button state
 * \return 1 for pressed, 0 otherwise
 */
char STGInput_ButtonState_Name_IsPressed(STGInput_ButtonState_Name buttonState);

/**
 * Get whether or not the button is pressed or repeat-pressed.
 * Repeat-pressed is true in the case of e.g. a keyboard character key being held down.
 *
 * \param buttonState current button state
 * \return 1 for pressed / repeat-pressed, 0 otherwise
 */
char STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_ButtonState_Name buttonState);

/**
 * Get whether or not the button is newly released this frame.
 *
 * \param buttonState current button state
 * \return 1 for released, 0 otherwise
 */
char STGInput_ButtonState_Name_IsReleased(STGInput_ButtonState_Name buttonState);

/**
 * Get whether or not the button is newly double-click this frame.
 *
 * \param buttonState current button state
 * \return 1 for double-click, 0 otherwise
 */
char STGInput_ButtonState_Name_IsDoubleClick(STGInput_ButtonState_Name buttonState);

/**
 * Get the string representation of a given button state.
 *
 * \param buttonState button state name enum value
 * \return button state name description string
 */
char* STGInput_ButtonState_Name_ToString(STGInput_ButtonState_Name buttonState);
