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

typedef enum STGInput_GamepadButtons
{
    // SDL_CONTROLER_BUTTON copies
    // TODO: Rename ABXY to up down left right?
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

typedef enum STGInput_GamepadAxes
{
    STGINPUT_GAMEPADAXES_STICK_LEFT_X,
    STGINPUT_GAMEPADAXES_STICK_LEFT_Y,
    STGINPUT_GAMEPADAXES_STICK_RIGHT_X,
    STGINPUT_GAMEPADAXES_STICK_RIGHT_Y,
    STGINPUT_GAMEPADAXES_TRIGGER_LEFT,
    STGINPUT_GAMEPADAXES_TRIGGER_RIGHT,
} STGInput_GamepadAxes;

static STGInput_GamepadAxes STGInput_GamepadAxes_List[STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES];
static SDL_GameControllerButton SDL_GameControllerButtons_To_STGInput_GamepadButtons_List[STGINPUT_GAMEPAD_BUTTONS_COUNT_BUTTONS];
static SDL_GameControllerAxis STGInput_GamepadAxesSDL[STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES];
static STGInput_GamepadButtons STGInput_GamepadButtons_List[STGINPUT_GAMEPAD_BUTTONS_COUNT];

typedef struct STGInput_GamepadAxis_Profile
{
    STGInput_GamepadAxes axis;
    STGInput_GamepadButtons button;
    float rangeBegin;
    float rangeEnd;
} STGInput_GamepadAxis_Profile;

typedef struct STGInput_GamepadStateProfile
{
    STGInput_ButtonState button[STGINPUT_GAMEPAD_BUTTONS_COUNT_BUTTONS];
} STGInput_GamepadStateProfile;

typedef struct STGInput_GamepadState STGInput_GamepadState;

typedef struct STGInput_GamepadStateList STGInput_GamepadStateList;

STGInput_GamepadState STGInput_GamepadState_Create(Sint32 which);

void STGInput_GamepadState_Destroy(STGInput_GamepadState* gamepad);

char STGInput_GamepadState_IsActive(STGInput_GamepadState* gamepad);

int STGInput_GamepadState_AxisSDLIndex(SDL_GameControllerAxis axis);

int STGInput_GamepadState_AxisIndex(STGInput_GamepadButtons axis);

float STGInput_GamepadState_AxisPercentage(STGInput_GamepadState* gamepad, STGInput_GamepadButtons axis);

Sint16 STGInput_GamepadState_AxisValue(STGInput_GamepadState* gamepad, STGInput_GamepadButtons axis);

int STGInput_GamepadState_ButtonIndex(STGInput_GamepadButtons button);

int STGInput_GamepadState_ButtonIndexSDL(SDL_GameControllerButton button);

STGInput_ButtonState_Name STGInput_GamepadState_Button_GetState(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

char STGInput_GamepadState_Button_IsDown(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

char STGInput_GamepadState_Button_IsPressed(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

char STGInput_GamepadState_Button_IsPressedOrRepeated(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

char STGInput_GamepadState_Button_IsReleased(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button);

STGInput_GamepadStateList* STGInput_GamepadStateList_Create();

int STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list, STGInput_GamepadState gamepad);

void STGInput_GamepadStateList_Remove(STGInput_GamepadStateList* list, Uint32 id);

STGInput_GamepadState* STGInput_GamepadStateList_FindById(STGInput_GamepadStateList* list, Uint32 id);

STGInput_GamepadState* STGInput_GamepadStateList_FindByIndex(STGInput_GamepadStateList* list, int index);

int STGInput_GamepadStateList_Index_FindById(STGInput_GamepadStateList* list, Uint32 id);

void STGInput_GamepadStateList_Event(STGInput_GamepadStateList* list, SDL_Event event);

void STGInput_GamepadStateList_SetAxesButtons(STGInput_GamepadStateList* list);

void STGInput_GamepadStateList_Update(STGInput_GamepadStateList* list);

STGInput_ButtonState_Name STGInput_GamepadStateList_Button_GetState(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button);

char STGInput_GamepadStateList_Button_IsDown(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button);

char STGInput_GamepadStateList_Button_IsPressed(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button);

char STGInput_GamepadStateList_Button_IsPressedOrRepeated(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button);

STGInput_GamepadStateProfile STGInput_GamepadStateProfile_Create();
