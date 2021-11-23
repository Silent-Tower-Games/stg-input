#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput.h"

// TODO: Gamepad state
// TODO: Gamepad state profile, wherein you can calibrate axes & remap buttons
// TODO: Mouse state
// TODO: Hide all struct properties & use functions directly with STGInput, or with a state returned from that
// TODO: Write comments

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
        
        if(STGInput_ButtonState_Name_IsDown(input->keyboard.button[1].state))
        {
            printf("Enter! `%s`\n", STGInput_ButtonState_Name_ToString(input->keyboard.button[1].state));
        }
        
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
        
        STGInput_Update(input);
    }
    
    STGInput_Destroy(input);
    
    return 0;
}
