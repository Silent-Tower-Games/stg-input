#include <SDL2/SDL.h>
#include "STGInput.h"

STGInput* STGInput_Create()
{
    STGInput* input = calloc(1, sizeof(STGInput));
    
    input->gamepads = STGInput_GamepadStateList_Create();
    input->keyboard = STGInput_KeyboardState_Create();
    input->mouse = STGInput_MouseState_Create();
    
    return input;
}

void STGInput_Event(STGInput* input, SDL_Event event)
{
    if(input == NULL)
    {
        return;
    }
    
    switch(event.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            STGInput_KeyboardState_Event(input->keyboard, event);
        } break;
        
        case SDL_CONTROLLERDEVICEADDED:
        case SDL_CONTROLLERDEVICEREMOVED:
        case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        case SDL_CONTROLLERAXISMOTION:
        {
            STGInput_GamepadStateList_Event(input->gamepads, event);
        } break;
        
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
        case SDL_MOUSEMOTION:
        case SDL_MOUSEWHEEL:
        {
            STGInput_MouseState_Event(input->mouse, event);
        } break;
    }
}

void STGInput_PreFrame(STGInput* input)
{
    if(input == NULL)
    {
        return;
    }
    
    STGInput_GamepadStateList_SetAxesButtons(input->gamepads);
}

void STGInput_PostFrame(STGInput* input)
{
    if(input == NULL)
    {
        return;
    }
    
    STGInput_KeyboardState_Update(input->keyboard);
    STGInput_GamepadStateList_Update(input->gamepads);
    STGInput_MouseState_Update(input->mouse);
}

void STGInput_Destroy(STGInput* input)
{
    if(input == NULL)
    {
        return;
    }
    
    STGInput_GamepadStateList_Destroy(input->gamepads);
    free(input->keyboard);
    free(input->mouse);
    
    free(input);
}
