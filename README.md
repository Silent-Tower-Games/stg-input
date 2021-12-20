# STGInput

An input library for SDL2 written in C.

## Example

```c
int main()
{
    // You must include these options when initializing
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER);
    
    // Create your input instance
    STGInput* input = STGInput_Create();
    
    // Your game loop (something like this)
    while(looping)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            STGInput_Event(event);
        }
        
        STGInput_PreFrame(input);
        
        // Handle input here
        
        // Get a gamepad state at index 0, aka Player One
        STGInput_GamepadState* gamepadPlayerOne = STGInput_GamepadStateList_FindByIndex(input->gamepads, 0);
        
        // See if the start button has been pressed
        if(STGInput_GamepadState_Button_IsPressed(gamepadPlayerOne, STGINPUT_GAMEPADBUTTONS_START))
        {
            // Will only fire on the frame the button was pressed
            // If held, it will not continue to fire
            printf("Start button pressed!\n");
        }
        
        STGInput_PostFrame(input);
    }
    
    STGInput_Destroy(input);
    
    return 0;
}
```

### Convenience Macros

If you want function names that aren't quite that verbose, you can include a header file that will define shortened macros.

```c
#define STGINPUT_CONVENIENCE
#include "STGInput/Convenience.h"

int logic()
{
    // If the mouse is double-clicking on this frame
    if(mouse(DoubleClick, LEFTCLICK))
    {
        printf("Double-click!\n");
    }
    
    // If the scroll wheel was scrolled this frame
    if(scroll().value != 0)
    {
        printf("Scroll wheel!\n");
    }
    
    // If the K key has been pressed or held down
    if(keyboard(PressedOrRepeated, k))
    {
        printf("Typing `k`\n");
    }
    
    // If the Face Down button was released this frame
    // (A on Xbox, B on Switch, X on PlayStation)
    if(gamepad(0, Released, FACE_DOWN))
    {
        printf("Released Face Down button! Initiating rumble...\n");
        
        // Will rumble at 25% power for 2 seconds, if the controller has rumble
        SDL_HapticRumblePlay(rumble(0), 0.25f, 2000);
    }
}
```
