#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput.h"

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
            gamepadPlayerOne = STGInput_GamepadStateList_FindByIndex(input->gamepads, 0);
        }
        
        // Keyboard tests
        if(STGInput_KeyboardState_Button_IsPressedOrRepeated(input->keyboard, STGINPUT_KEYBOARDKEYS_RETURN))
        {
            printf("Enter Pressed Or Repeated\n");
        }
        
        if(STGInput_KeyboardState_Button_IsPressed(input->keyboard, STGINPUT_KEYBOARDKEYS_LSHIFT))
        {
            printf("Left Shift Pressed\n");
        }
        
        if(STGInput_KeyboardState_Button_IsDown(input->keyboard, STGINPUT_KEYBOARDKEYS_a))
        {
            printf("A Down\n");
        }
        
        if(STGInput_KeyboardState_Button_IsReleased(input->keyboard, STGINPUT_KEYBOARDKEYS_b))
        {
            printf("B Released\n");
        }
        
        // Mouse tests
        if(STGInput_MouseState_Button_IsPressed(input->mouse, STGINPUT_MOUSEBUTTONS_LEFTCLICK))
        {
            printf("Left Click Pressed\n");
        }
        
        // Approximately 60fps. Doesn't need to be perfect for this test
        SDL_Delay(16);
        
        STGInput_PostFrame(input);
    }
    
    STGInput_Destroy(input);
    
    return 0;
}
