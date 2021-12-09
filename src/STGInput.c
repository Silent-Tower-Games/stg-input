#include <SDL2/SDL.h>
#include "STGInput.h"

STGInput* STGInput_Create()
{
    STGInput* input = calloc(1, sizeof(STGInput));
    
    return input;
}

void STGInput_Event(STGInput* input, SDL_Event event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            STGInput_KeyboardState_Event(&input->keyboard, event);
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

void STGInput_Update(STGInput* input)
{
    STGInput_KeyboardState_Update(&input->keyboard);
    STGInput_GamepadStateList_Update(&input->gamepads);
}

void STGInput_Destroy(STGInput* input)
{
    free(input);
}
