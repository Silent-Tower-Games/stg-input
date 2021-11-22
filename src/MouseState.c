#include <SDL2/SDL.h>
#include "MouseState.h"

void STGInput_MouseState_Update(STGInput_MouseState* mouseState)
{
    Uint32 state = SDL_GetMouseState(&mouseState->X, &mouseState->Y);
    
    //
}
