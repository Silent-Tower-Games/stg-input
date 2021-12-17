#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput/STGInput.h"
#define STGINPUT_CONVENIENCE
#include "STGInput/Convenience.h"

// TODO: Convenience functions, optional
// TODO: README

void init();
void events();

STGInput_GamepadState* gamepadPlayerOne = NULL;
SDL_Window* window;
SDL_Event event;
int quit = 0;

int main()
{
    init();
    
    printf("Hello, World!\n");
    
    while(!quit)
    {
        events();
        
        inputPreframe();
        
        // Gamepad tests
        if(gamepad(0, Pressed, FACE_DOWN))
        {
            printf("A Button Pressed\n");
        }
        
        if(keyboard(Down, a))
        {
            printf("A Key Down\n");
        }
        
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
        
        inputPostframe();
    }
    
    inputDestroy();
    
    return 0;
}

void init()
{
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER);
    
    STGInput* input = STGInput_Create();
    
    window = SDL_CreateWindow(
        "STG Input",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        360,
        0
    );
}

void events()
{
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                quit = 1;
            } break;
        }
        
        inputEvent(event);
    }
}
