#pragma once

#include <SDL2/SDL.h>
#include "ButtonState.h"

#define STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT 8
#define STGINPUT_GAMEPADSTATE_ID_INVALID -1
#define STGINPUT_GAMEPADSTATE_INDEX_INVALID -1

typedef enum STGInput_GamepadButtons
{
    // SDL_CONTROLER_BUTTON copies
    // TODO: Rename ABXY to up down left right?
    STGINPUT_GAMEPADBUTTONS_A,
    STGINPUT_GAMEPADBUTTONS_B,
    STGINPUT_GAMEPADBUTTONS_X,
    STGINPUT_GAMEPADBUTTONS_Y,
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
    // Additional
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

static STGInput_GamepadButtons STGInput_GamepadButtons_To_SDL_GameControllerButtons[15];
static SDL_GameControllerButton SDL_GameControllerButtons_To_STGInput_GamepadButtons[15];

typedef struct STGInput_GamepadStateProfile
{
    STGInput_ButtonState button[15];
} STGInput_GamepadStateProfile;

typedef struct STGInput_GamepadState
{
    SDL_JoystickID id;
    STGInput_ButtonState button[25];
    SDL_Haptic* haptic;
    SDL_Joystick* joystick;
    SDL_GameController* controller;
} STGInput_GamepadState;

typedef struct STGInput_GamepadStateList
{
    int allocated;
    int highest;
    STGInput_GamepadState* states;
} STGInput_GamepadStateList;

STGInput_GamepadState STGInput_GamepadState_Create(Sint32 which);

void STGInput_GamepadState_Destroy(STGInput_GamepadState* gamepad);

int STGInput_GamepadState_ButtonIndex(SDL_GameControllerButton button);

STGInput_GamepadStateList STGInput_GamepadStateList_Create();

int STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list, STGInput_GamepadState gamepad);

void STGInput_GamepadStateList_Remove(STGInput_GamepadStateList* list, Uint32 id);

STGInput_GamepadState* STGInput_GamepadStateList_FindById(STGInput_GamepadStateList* list, Uint32 id);

int STGInput_GamepadStateList_Index_FindById(STGInput_GamepadStateList* list, Uint32 id);

void STGInput_GamepadStateList_Event(STGInput_GamepadStateList* list, SDL_Event event);

void STGInput_GamepadStateList_Update(STGInput_GamepadStateList* list);

STGInput_GamepadStateProfile STGInput_GamepadStateProfile_Create();
