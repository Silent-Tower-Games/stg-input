#pragma once

#define STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT 8

typedef enum STGInput_GamepadButtons
{
    GPB_INVALID = -1,
    // SDL_CONTROLER_BUTTON copies
    GPB_A,
    GPB_B,
    GPB_X,
    GPB_Y,
    GPB_BACK,
    GPB_GUIDE,
    GPB_START,
    GPB_STICK_LEFT,
    GPB_STICK_RIGHT,
    GPB_SHOULDER_LEFT,
    GPB_SHOULDER_RIGHT,
    GPB_DPAD_UP,
    GPB_DPAD_DOWN,
    GPB_DPAD_LEFT,
    GPB_DPAD_RIGHT,
    // Additional
    GPB_TRIGGER_LEFT,
    GPB_TRIGGER_RIGHT,
    GPB_STICK_LEFT_LEFT,
    GPB_STICK_LEFT_RIGHT,
    GPB_STICK_LEFT_DOWN,
    GPB_STICK_LEFT_UP,
    GPB_STICK_RIGHT_LEFT,
    GPB_STICK_RIGHT_RIGHT,
    GPB_STICK_RIGHT_DOWN,
    GPB_STICK_RIGHT_UP,
} STGInput_GamepadButtons;

typedef struct STGInput_GamepadState
{
    int test;
} STGInput_GamepadState;

typedef struct STGInput_GamepadStateList
{
    int allocated;
    int count;
    STGInput_GamepadState* states;
} STGInput_GamepadStateList;

STGInput_GamepadStateList STGInput_GamepadStateList_Create();

void STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list);

void STGInput_GamepadState_Event(STGInput_GamepadStateList* gamepadStateList);
