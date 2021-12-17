#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput.h"

void init();
void events();

STGInput_GamepadState* gamepadPlayerOne = NULL;
SDL_Window* window;
SDL_Event event;
STGInput* input;
int quit = 0;

int main()
{
    init();
    
    input = STGInput_Create();
    
    while(!quit)
    {
        events();
        
        STGInput_PreFrame(input);
        
        // Gamepad tests
        if(gamepadPlayerOne == NULL)
        {
            gamepadPlayerOne = STGInput_GamepadStateList_FindByIndex(input->gamepads, 0);
        }
        
        if(STGInput_GamepadState_Button_IsPressed(gamepadPlayerOne, STGINPUT_GAMEPADBUTTONS_FACE_DOWN))
        {
            printf("A Button Down\n");
        }
        
        if(STGInput_GamepadState_Button_IsPressed(gamepadPlayerOne, STGINPUT_GAMEPADBUTTONS_BACK))
        {
            printf("Back Button Pressed; Quitting\n");
            
            break;
        }
        
        if(STGInput_GamepadState_Button_IsPressed(gamepadPlayerOne, STGINPUT_GAMEPADBUTTONS_STICK_RIGHT_RIGHT))
        {
            printf("Right Stick Held Right: %1.3f\n", STGInput_GamepadState_AxisPercentage(gamepadPlayerOne, STGINPUT_GAMEPADAXES_STICK_RIGHT_X));
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
            printf("A Key Down\n");
        }
        
        if(STGInput_KeyboardState_Button_IsReleased(input->keyboard, STGINPUT_KEYBOARDKEYS_b))
        {
            printf("B Key Released\n");
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
        
        STGInput_Event(input, event);
    }
}
