#include <assert.h>
#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include "STGInput/STGInput.h"
#include "STGInput/ButtonState.h"
#define STGINPUT_CONVENIENCE
#include "STGInput/Convenience.h"

// TODO: README

void init();
void events();

STGInput_GamepadState* gamepadPlayerOne = NULL;
SDL_Renderer* renderer;
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
        if(gamepadPlayerOne == NULL)
        {
            gamepadPlayerOne = gamepadObjGet(0);
            
            printf(
                "%s\n",
                gamepadPlayerOne ? "---" : SDL_JoystickName(STGInput_GamepadState_GetJoystick(gamepadPlayerOne))
            );
        }
        
        if(gamepad(0, Pressed, FACE_DOWN))
        {
            printf("A Button Pressed :)\n");
            
            SDL_HapticRumblePlay(rumble(0), 0.25f, 2000);
        }
        
        if(gamepadObj(gamepadPlayerOne, Pressed, START))
        {
            printf("Start Button Pressed!\n");
            
            SDL_HapticRumblePlay(rumbleObj(gamepadPlayerOne), 1.0f, 500);
        }
        
        // Keyboard tests
        if(keyboard(Down, a))
        {
            printf("A Key Down\n");
        }
        
        // Mouse tests
        if(mouse(DoubleClick, LEFTCLICK))
        {
            STGInput_MousePosition pos = mousePos();
            printf("%dx%d\n", pos.X, pos.Y);
        }
        
        if(mouse(Down, MIDDLECLICK))
        {
            printf("Middle Click\n");
        }
        
        if(scroll().value != 0)
        {
            printf("Scrolled: %d or %1.1f\n", scroll().value, scroll().percentage);
        }
        
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
        
        inputPostframe();
        
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    
    inputDestroy();
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    return 0;
}

void init()
{
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER);
    
    window = SDL_CreateWindow(
        "STG Input",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        360,
        0
    );
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
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
