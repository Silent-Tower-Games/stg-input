#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput.h"

// Doing:
// TODO: Gamepad axes to button values

// Later:
// TODO: Gamepad state profile, wherein you can calibrate axes & remap buttons
// TODO: Mouse state
// TODO: Hide all struct properties & use functions directly with STGInput, or with a state returned from that
// TODO: Write comments
// TODO: Unit tests

int main()
{
    printf("Hello, World!\n");
    
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER);
    
    STGInput* input = STGInput_Create();
    
    SDL_Event event;
    
    SDL_Window* window = SDL_CreateWindow(
        "STG Input",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        360,
        0
    );
    
    STGInput_GamepadState* gamepadPlayerOne = NULL;
    int quit = 0;
    
    while(!quit)
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
            
            STGInput_Event(input, event);
        }
        
        if(gamepadPlayerOne == NULL)
        {
            printf("Setting...\n");
            gamepadPlayerOne = STGInput_GamepadStateList_FindByIndex(&input->gamepads, 0);
        }
        
        if(STGInput_GamepadState_Button_IsDown(gamepadPlayerOne, STGINPUT_GAMEPADBUTTONS_FACE_DOWN))
        {
            printf(
                "%1.3f\n",
                STGInput_GamepadState_AxisPercentage(gamepadPlayerOne, STGINPUT_GAMEPADAXES_LEFT_X)
            );
        }
        
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
        
        STGInput_PostFrame(input);
    }
    
    STGInput_Destroy(input);
    
    return 0;
}
