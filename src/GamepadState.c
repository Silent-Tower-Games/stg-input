#include <stdlib.h>
#include <math.h>
#include "GamepadState.h"

STGInput_GamepadState STGInput_GamepadState_Create(Sint32 which)
{
    STGInput_GamepadState gamepad;
    memset(&gamepad, 0, sizeof(gamepad));
    
    gamepad.joystick = SDL_JoystickOpen(which);
    gamepad.id = SDL_JoystickInstanceID(gamepad.joystick);
    gamepad.controller = SDL_GameControllerOpen(which);
    gamepad.haptic = SDL_HapticOpen(which);
    
    // Require everything to be valid except haptic
    // Some controllers don't need haptic
    // TODO: Can we get away with just a Joystick? Idk if GameController is necessary
    if(
        gamepad.joystick == NULL
        ||
        gamepad.controller == NULL
        ||
        gamepad.id <= STGINPUT_GAMEPADSTATE_ID_INVALID
    )
    {
        STGInput_GamepadState_Destroy(&gamepad);
    }
    
    return gamepad;
}

void STGInput_GamepadState_Destroy(STGInput_GamepadState* gamepad)
{
    // FIXME: NULL check
    
    SDL_HapticClose(gamepad->haptic);
    SDL_GameControllerClose(gamepad->controller);
    SDL_JoystickClose(gamepad->joystick);
    gamepad->id = STGINPUT_GAMEPADSTATE_ID_INVALID;
}

int STGInput_GamepadState_AxisSDLIndex(SDL_GameControllerAxis axis)
{
    for(int i = 0; i < STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES; i++)
    {
        if(STGInput_GamepadAxesSDL[i] != axis)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

int STGInput_GamepadState_AxisIndex(STGInput_GamepadButtons axis)
{
    for(int i = 0; i < STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES; i++)
    {
        if(STGInput_GamepadAxesSTGInput[i] != axis)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

float STGInput_GamepadState_AxisPercentage(STGInput_GamepadState* gamepad, STGInput_GamepadButtons axis)
{
    // FIXME: NULL check
    
    int index = STGInput_GamepadState_AxisIndex(axis);
    
    printf("i %d\n", index);
    
    if(index < 0 || index >= STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES)
    {
        return 0.0f;
    }
    
    return gamepad->axis[index].percentage;
}

Sint16 STGInput_GamepadState_AxisValue(STGInput_GamepadState* gamepad, STGInput_GamepadButtons axis)
{
    // FIXME: NULL check
    
    int index = STGInput_GamepadState_AxisIndex(axis);
    
    if(index < 0 || index >= STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES)
    {
        return 0.0f;
    }
    
    return gamepad->axis[index].value;
}

int STGInput_GamepadState_ButtonIndex(SDL_GameControllerButton button)
{
    for(int i = 0; i < STGINPUT_GAMEPAD_BUTTONS_COUNT_BUTTONS; i++)
    {
        if(SDL_GameControllerButtons_To_STGInput_GamepadButtons[i] != button)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

STGInput_ButtonState_Name STGInput_GamepadState_Button_GetState(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    if(gamepad == NULL)
    {
        return STGINPUT_BUTTONSTATE_NAME_UP;
    }
    
    int index = STGInput_GamepadState_ButtonIndex(button);
    
    if(index < 0 || index >= STGINPUT_GAMEPAD_BUTTONS_COUNT)
    {
        return STGINPUT_BUTTONSTATE_NAME_UP;
    }
    
    return gamepad->button[index].state;
}

char STGInput_GamepadState_Button_IsDown(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    return STGInput_ButtonState_Name_IsDown(STGInput_GamepadState_Button_GetState(gamepad, button));
}

char STGInput_GamepadState_Button_IsPressed(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    return STGInput_ButtonState_Name_IsPressed(STGInput_GamepadState_Button_GetState(gamepad, button));
}

char STGInput_GamepadState_Button_IsPressedOrRepeated(STGInput_GamepadState* gamepad, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    return STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_GamepadState_Button_GetState(gamepad, button));
}

static void STGInput_GamepadStateList_Expand(STGInput_GamepadStateList* list)
{
    // FIXME: NULL check
    
    const int allocatedOriginal = list->allocated;
    
    list->allocated += STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT;
    list->states = realloc(list->states, sizeof(STGInput_GamepadState) * list->allocated);
    
    for(int i = allocatedOriginal; i < list->allocated; i++)
    {
        list->states[i].id = STGINPUT_GAMEPADSTATE_ID_INVALID;
    }
}

STGInput_GamepadStateList STGInput_GamepadStateList_Create()
{
    STGInput_GamepadStateList list;
    memset(&list, 0, sizeof(list));
    
    STGInput_GamepadStateList_Expand(&list);
    
    return list;
}

int STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list, STGInput_GamepadState gamepad)
{
    // FIXME: NULL check
    
    if(gamepad.id <= STGINPUT_GAMEPADSTATE_ID_INVALID)
    {
        return STGINPUT_GAMEPADSTATE_INDEX_INVALID;
    }
    
    // Look for an empty state to fill
    for(int i = 0; i < list->allocated; i++)
    {
        if(list->states[i].id != STGINPUT_GAMEPADSTATE_ID_INVALID)
        {
            continue;
        }
        
        list->states[i] = gamepad;
        
        list->highest = fmax(list->highest, i);
        
        return i;
    }
    
    // If you can't find an empty state within count, expand the list
    const int allocatedOriginal = list->allocated;
    
    STGInput_GamepadStateList_Expand(list);
    
    list->states[allocatedOriginal] = gamepad;
    
    list->highest = fmax(list->highest, allocatedOriginal);
    
    return allocatedOriginal;
}

void STGInput_GamepadStateList_Remove(STGInput_GamepadStateList* list, Uint32 id)
{
    // FIXME: NULL check
    
    int gamepadIndex = STGInput_GamepadStateList_Index_FindById(list, id);
    
    if(gamepadIndex <= STGINPUT_GAMEPADSTATE_ID_INVALID)
    {
        return;
    }
    
    STGInput_GamepadState_Destroy(&list->states[gamepadIndex]);
    
    if(gamepadIndex == list->highest)
    {
        int nextHighest = -1;
        
        // FIXME: This should start with highest-1 and count down to 0
        for(int i = 0; i < list->highest; i++)
        {
            if(list->states[i].id <= STGINPUT_GAMEPADSTATE_ID_INVALID)
            {
                continue;
            }
            
            nextHighest = fmax(nextHighest, i);
        }
        
        list->highest = nextHighest;
    }
}

STGInput_GamepadState* STGInput_GamepadStateList_FindById(STGInput_GamepadStateList* list, Uint32 id)
{
    // FIXME: NULL check
    
    int gamepadIndex = STGInput_GamepadStateList_Index_FindById(list, id);
    
    if(gamepadIndex == -1)
    {
        return NULL;
    }
    
    return &list->states[gamepadIndex];
}

int STGInput_GamepadStateList_Index_FindById(STGInput_GamepadStateList* list, Uint32 id)
{
    // FIXME: NULL check
    
    for(int i = 0; i <= list->highest; i++)
    {
        if(list->states[i].id != id)
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

STGInput_GamepadState* STGInput_GamepadStateList_FindByIndex(STGInput_GamepadStateList* list, int index)
{
    // FIXME: NULL check
    
    if(index < 0 || index >= list->allocated)
    {
        return NULL;
    }
    
    return &list->states[index];
}

void STGInput_GamepadStateList_Event(STGInput_GamepadStateList* list, SDL_Event event)
{
    // FIXME: NULL check
    
    switch(event.type)
    {
        case SDL_CONTROLLERDEVICEADDED:
        {
            STGInput_GamepadState gamepad = STGInput_GamepadState_Create(event.cdevice.which);
            
            const int index = STGInput_GamepadStateList_Add(list, gamepad);
        } break;
        
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            STGInput_GamepadStateList_Remove(list, event.cdevice.which);
        } break;
        
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        {
            STGInput_GamepadState* gamepad = STGInput_GamepadStateList_FindById(list, event.cdevice.which);
            
            if(gamepad == NULL)
            {
                break;
            }
            
            int buttonIndex = STGInput_GamepadState_ButtonIndex(event.cbutton.button);
                
            char isDown = event.type == SDL_CONTROLLERBUTTONDOWN ?
                STGINPUT_BUTTONSTATE_EVENT_DOWN
            :
                STGINPUT_BUTTONSTATE_EVENT_UP
            ;
            
            gamepad->button[buttonIndex] = STGInput_ButtonState_Event(
                gamepad->button[buttonIndex],
                isDown,
                STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT
            );
        } break;
        
        case SDL_CONTROLLERAXISMOTION:
        {
            STGInput_GamepadState* gamepad = STGInput_GamepadStateList_FindById(list, event.cdevice.which);
            
            if(gamepad == NULL)
            {
                break;
            }
            
            int axisIndex = STGInput_GamepadState_AxisIndex(event.caxis.axis);
            
            gamepad->axis[axisIndex] = STGInput_AxisState_Update(gamepad->axis[axisIndex], event.caxis.value);
        } break;
    }
}

void STGInput_GamepadStateList_Update(STGInput_GamepadStateList* list)
{
    // FIXME: NULL check
    
    for(int i = 0; i <= list->highest; i++)
    {
        if(list->states[i].id <= STGINPUT_GAMEPADSTATE_ID_INVALID)
        {
            continue;
        }
        
        for(int j = 0; j < STGINPUT_GAMEPAD_BUTTONS_COUNT; j++)
        {
            list->states[i].button[j] = STGInput_ButtonState_Update(list->states[i].button[j]);
        }
    }
}

STGInput_ButtonState_Name STGInput_GamepadStateList_Button_GetState(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    if(index < 0 || index >= list->highest || list->states[index].id <= STGINPUT_GAMEPADSTATE_ID_INVALID)
    {
        return STGINPUT_BUTTONSTATE_NAME_UP;
    }
    
    return STGInput_GamepadState_Button_GetState(&list->states[index], button);
}

char STGInput_GamepadStateList_Button_IsDown(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    return STGInput_ButtonState_Name_IsDown(STGInput_GamepadState_Button_GetState(&list->states[index], button));
}

char STGInput_GamepadStateList_Button_IsPressed(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    return STGInput_ButtonState_Name_IsPressed(STGInput_GamepadState_Button_GetState(&list->states[index], button));
}

char STGInput_GamepadStateList_Button_IsPressedOrRepeated(STGInput_GamepadStateList* list, int index, STGInput_GamepadButtons button)
{
    // FIXME: NULL check
    
    return STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_GamepadState_Button_GetState(&list->states[index], button));
}

STGInput_GamepadStateProfile STGInput_GamepadStateProfile_Create()
{
    STGInput_GamepadStateProfile profile;
    memcpy(
        &profile.button,
        &SDL_GameControllerButtons_To_STGInput_GamepadButtons,
        sizeof(SDL_GameControllerButtons_To_STGInput_GamepadButtons)
    );
}

static STGInput_GamepadButtons STGInput_GamepadButtons_To_SDL_GameControllerButtons[STGINPUT_GAMEPAD_BUTTONS_COUNT_BUTTONS] = {
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
};

static SDL_GameControllerButton SDL_GameControllerButtons_To_STGInput_GamepadButtons[STGINPUT_GAMEPAD_BUTTONS_COUNT_BUTTONS] = {
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

static SDL_GameControllerAxis STGInput_GamepadAxesSDL[STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES] = {
    SDL_CONTROLLER_AXIS_LEFTX,
    SDL_CONTROLLER_AXIS_LEFTY,
    SDL_CONTROLLER_AXIS_RIGHTX,
    SDL_CONTROLLER_AXIS_RIGHTY,
    SDL_CONTROLLER_AXIS_TRIGGERLEFT,
    SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
};

static STGInput_GamepadAxes STGInput_GamepadAxesSTGInput[STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES] = {
    STGINPUT_GAMEPADAXES_LEFT_X,
    STGINPUT_GAMEPADAXES_LEFT_Y,
    STGINPUT_GAMEPADAXES_RIGHT_X,
    STGINPUT_GAMEPADAXES_RIGHT_Y,
    STGINPUT_GAMEPADAXES_TRIGGER_LEFT,
    STGINPUT_GAMEPADAXES_TRIGGER_RIGHT,
};