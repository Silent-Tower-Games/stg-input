#pragma once

#include <SDL2/SDL.h>
#include "ButtonState.h"

#define STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT 8

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

typedef struct STGInput_GamepadState
{
    Sint32 id;
    STGInput_ButtonState button[25];
    SDL_Haptic* haptic;
    SDL_Joystick* joystick;
    SDL_GameController* controller;
} STGInput_GamepadState;

typedef struct STGInput_GamepadStateList
{
    int allocated;
    int count;
    STGInput_GamepadState* states;
} STGInput_GamepadStateList;

STGInput_GamepadState STGInput_GamepadState_Create(Sint32 which);

void STGInput_GamepadState_Destroy(STGInput_GamepadState* gamepad);

STGInput_GamepadStateList STGInput_GamepadStateList_Create();

void STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list, STGInput_GamepadState gamepad);

void STGInput_GamepadStateList_Event(STGInput_GamepadStateList* list, SDL_Event event);

void STGInput_GamepadStateList_Update(STGInput_GamepadStateList* list);

int STGInput_GamepadState_ButtonIndex(SDL_GameControllerButton button);
