#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput.h"

int main()
{
    printf("Hello, World!\n");
    
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER);
    
    while(1)
    {
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
    }
    
    return 0;
}
