#include <stdlib.h>
#include "GamepadState.h"

static void STGInput_GamepadStateList_Expand(STGInput_GamepadStateList* list)
{
    list->allocated += STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT;
    list->states = realloc(list->states, sizeof(STGInput_GamepadState) * list->allocated);
}

STGInput_GamepadState STGInput_GamepadState_Create(Sint32 which)
{
    STGInput_GamepadState gamepad;
    memset(&gamepad, 0, sizeof(gamepad));
    
    gamepad.joystick = SDL_JoystickOpen(which);
    gamepad.controller = SDL_GameControllerOpen(which);
    gamepad.haptic = SDL_HapticOpen(which);
    
    return gamepad;
}

void STGInput_GamepadState_Destroy(STGInput_GamepadState* gamepad)
{
    SDL_HapticClose(gamepad->haptic);
    SDL_GameControllerClose(gamepad->controller);
    SDL_JoystickClose(gamepad->joystick);
}

STGInput_GamepadStateList STGInput_GamepadStateList_Create()
{
    STGInput_GamepadStateList list;
    memset(&list, 0, sizeof(list));
    
    STGInput_GamepadStateList_Expand(&list);
    
    return list;
}

void STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list, STGInput_GamepadState gamepad)
{
    if(list->count >= list->allocated)
    {
        STGInput_GamepadStateList_Expand(list);
    }
    
    list->states[list->count] = gamepad;
    
    list->count++;
}

void STGInput_GamepadStateList_Event(STGInput_GamepadStateList* list, SDL_Event event)
{
    switch(event.type)
    {
        case SDL_CONTROLLERDEVICEADDED:
        {
            STGInput_GamepadState gamepad = STGInput_GamepadState_Create(event.cdevice.which);
            
            // Possibly add some validation here? Make sure that there's at least one not-null value?
            STGInput_GamepadStateList_Add(list, gamepad);
            
            printf("Added gamepad: `%s`\n", SDL_JoystickName(gamepad.joystick));
        } break;
        
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            printf("Removed gamepad: `%s`\n", SDL_JoystickNameForIndex(event.cdevice.which));
        } break;
        
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        {
            for(int i = 0; i < list->count; i++)
            {
                if(list->states[i].id != event.cdevice.which)
                {
                    continue;
                }
                
                int j = STGInput_GamepadState_ButtonIndex(event.cbutton.button);
                
                char isDown = event.type == SDL_CONTROLLERBUTTONDOWN ?
                    STGINPUT_BUTTONSTATE_EVENT_DOWN
                :
                    STGINPUT_BUTTONSTATE_EVENT_UP
                ;
                
                list->states[i].button[j] = STGInput_ButtonState_Event(
                    list->states[i].button[j],
                    isDown,
                    STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT
                );
                
                break;
            }
        } break;
    }
}

void STGInput_GamepadStateList_Update(STGInput_GamepadStateList* list)
{
    for(int i = 0; i < list->count; i++)
    {
        for(int j = 0; j < 25; j++)
        {
            list->states[i].button[j] = STGInput_ButtonState_Update(list->states[i].button[j]);
        }
    }
}

int STGInput_GamepadState_ButtonIndex(SDL_GameControllerButton button)
{
    for(int i = 0; i < 15; i++)
    {
        if(SDL_GameControllerButtons_To_STGInput_GamepadButtons[i] != button)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

static STGInput_GamepadButtons STGInput_GamepadButtons_To_SDL_GameControllerButtons[15] = {
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
};

static SDL_GameControllerButton SDL_GameControllerButtons_To_STGInput_GamepadButtons[15] = {
    SDL_CONTROLLER_BUTTON_A,
    SDL_CONTROLLER_BUTTON_B,
    SDL_CONTROLLER_BUTTON_X,
    SDL_CONTROLLER_BUTTON_Y,
    SDL_CONTROLLER_BUTTON_BACK,
    SDL_CONTROLLER_BUTTON_GUIDE,
    SDL_CONTROLLER_BUTTON_START,
    SDL_CONTROLLER_BUTTON_LEFTSTICK,
    SDL_CONTROLLER_BUTTON_RIGHTSTICK,
    SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
    SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    SDL_CONTROLLER_BUTTON_DPAD_UP,
    SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    SDL_CONTROLLER_BUTTON_DPAD_RIGHT,
};
