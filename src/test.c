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
// TODO: Fix names. They've gotten out of hand

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
        
        STGInput_PreFrame(input);
        
        if(gamepadPlayerOne == NULL)
        {
            printf("Setting...\n");
            gamepadPlayerOne = STGInput_GamepadStateList_FindByIndex(&input->gamepads, 0);
        }
        
        STGInput_GamepadAxes_Profile axes[STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES_BUTTONS] = {
            { STGINPUT_GAMEPADAXES_TRIGGER_LEFT, STGINPUT_GAMEPADBUTTONS_TRIGGER_LEFT, 0.5f, 1.0f, },
            { STGINPUT_GAMEPADAXES_TRIGGER_RIGHT, STGINPUT_GAMEPADBUTTONS_TRIGGER_RIGHT, 0.5f, 1.0f, },
            { STGINPUT_GAMEPADAXES_STICK_LEFT_X, STGINPUT_GAMEPADBUTTONS_STICK_LEFT_LEFT, -1.0f, -0.5f, },
            { STGINPUT_GAMEPADAXES_STICK_LEFT_X, STGINPUT_GAMEPADBUTTONS_STICK_LEFT_RIGHT, 0.5f, 1.0f, },
            { STGINPUT_GAMEPADAXES_STICK_LEFT_Y, STGINPUT_GAMEPADBUTTONS_STICK_LEFT_UP, -1.0f, -0.5f, },
            { STGINPUT_GAMEPADAXES_STICK_LEFT_Y, STGINPUT_GAMEPADBUTTONS_STICK_LEFT_DOWN, 0.5f, 1.0f, },
            { STGINPUT_GAMEPADAXES_STICK_RIGHT_X, STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_LEFT, -1.0f, -0.5f, },
            { STGINPUT_GAMEPADAXES_STICK_RIGHT_X, STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_RIGHT, 0.5f, 1.0f, },
            { STGINPUT_GAMEPADAXES_STICK_RIGHT_Y, STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_UP, -1.0f, -0.5f, },
            { STGINPUT_GAMEPADAXES_STICK_RIGHT_Y, STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_DOWN, 0.5f, 1.0f, },
        };
        
        for(int i = 0; i < STGINPUT_GAMEPAD_BUTTONS_COUNT_AXES_BUTTONS; i++)
        {
            if(STGInput_GamepadState_Button_IsDown(gamepadPlayerOne, axes[i].button))
            {
                printf(
                    "%d: %1.3f\n",
                    i,
                    STGInput_GamepadState_AxisPercentage(gamepadPlayerOne, axes[i].axis)
                );
            }
        }
        
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
        
        STGInput_PostFrame(input);
    }
    
    STGInput_Destroy(input);
    
    return 0;
}
