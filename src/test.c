#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput/STGInput.h"
#include "STGInput/Convenience.h"

// TODO: IsDoubleClick function
// TODO: Switch mouse stuff to events
// TODO: Convenience functions, optional
// TODO: README
// TODO: Scroll wheel
// TODO: Haptic

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
        if(gamepadPlayerOne == NULL)
        {
            gamepadPlayerOne = STGInput_GamepadStateList_FindByIndex(STGInput_Convenience_InputState_Getter()->gamepads, 0);
        }
        
        if(gamepad(0, Pressed, FACE_DOWN))
        {
            printf("A Button Pressed\n");
        }
        
        if(gamepadObj(gamepadPlayerOne, Pressed, START))
        {
            printf("Start Button Pressed\n");
        }
        
        // Keyboard tests
        if(keyboard(Down, a))
        {
            printf("A Key Down\n");
        }
        
        // Mouse tests
        if(mouse(Pressed, LEFTCLICK))
        {
            STGInput_MousePosition pos = mousePos();
            printf("%dx%d\n", pos.X, pos.Y);
        }
        
        if(mouse(Down, MIDDLECLICK))
        {
            printf("Middle Click\n");
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
