#include <SDL2/SDL.h>
#include "STGInput.h"

STGInput* STGInput_Create()
{
    STGInput* input = calloc(1, sizeof(STGInput));
    
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
            STGInput_GamepadStateList_Event(&input->gamepads, event);
        } break;
    }
}

void STGInput_PreFrame(STGInput* input)
{
    if(input == NULL)
    {
        return;
    }
    
    STGInput_GamepadStateList_SetAxesButtons(&input->gamepads);
    STGInput_MouseState_Poll(input->mouse);
}

void STGInput_PostFrame(STGInput* input)
{
    if(input == NULL)
    {
        return;
    }
    
    STGInput_KeyboardState_Update(input->keyboard);
    STGInput_GamepadStateList_Update(&input->gamepads);
    STGInput_MouseState_Update(input->mouse);
}

void STGInput_Destroy(STGInput* input)
{
    if(input == NULL)
    {
        return;
    }
    
    // FIXME: Destroy all allocated memory inside input manager
    
    free(input);
}
