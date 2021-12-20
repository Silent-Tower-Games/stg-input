#include <assert.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "STGInput/STGInput.h"
#include "STGInput/ButtonState.h"
#define STGINPUT_CONVENIENCE
#include "STGInput/Convenience.h"

// TODO: README

void init();
void events();
void tests();

STGInput_GamepadState* gamepadPlayerOne = NULL;
SDL_Window* window;
SDL_Event event;
int quit = 0;

int main()
{
    tests();
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
            printf("A Button Pressed :)\n");
            
            SDL_HapticRumblePlay(rumble(0), 0.25f, 2000);
        }
        
        if(gamepadObj(gamepadPlayerOne, Pressed, START))
        {
            printf("Start Button Pressed!!!!!!!!!!!!\n");
            
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

#define testAssert(claim) { if(!claim){ assert(claim); }else{ printf("Test passed `%s'\n", # claim); } }
#define testCompare(a, b) { if(a != b){\
    printf("`%s' (%d) does not equal `%s' (%d)!\n", # a, a, # b, b); assert(a == b);\
}else{ testAssert(a == b); } }

void tests()
{
    // Make sure ButtonState behaves as it should
    STGInput_ButtonState buttonStateClean = {
        .lastPressed = 0,
        .state = STGINPUT_BUTTONSTATE_NAME_UP,
        .value = 0.0f,
    };
    STGInput_ButtonState buttonState;
    
    // Make sure it reaches PRESSED state, then DOWN state after update
    // Then RELEASED after event, then UP after update
    buttonState = buttonStateClean;
    buttonState = STGInput_ButtonState_Event(buttonState, 1, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_PRESSED);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_DOWN);
    buttonState = STGInput_ButtonState_Event(buttonState, 0, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_RELEASED);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_UP);
    
    // Make sure it reaches PRESSED_THEN_RELEASED state, then RELEASED after update, then UP after update
    buttonState = buttonStateClean;
    buttonState = STGInput_ButtonState_Event(buttonState, 1, 0);
    buttonState = STGInput_ButtonState_Event(buttonState, 0, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_RELEASED);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_UP);
    
    // Make sure it reaches PRESSED_THEN_RELEASED state, then RELEASED after update
    // Then DOUBLECLICK after event, then DOUBLECLICK_THEN_RELEASED after event
    buttonState = buttonStateClean;
    buttonState = STGInput_ButtonState_Event(buttonState, 1, 0);
    buttonState = STGInput_ButtonState_Event(buttonState, 0, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_RELEASED);
    buttonState = STGInput_ButtonState_Event(buttonState, 1, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK);
    buttonState = STGInput_ButtonState_Event(buttonState, 0, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED);
    
    // Make sure REPEAT works correctly
    buttonState = buttonStateClean;
    buttonState = STGInput_ButtonState_Event(buttonState, 1, 0);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_PRESSED);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_DOWN);
    buttonState = STGInput_ButtonState_Event(buttonState, 1, 1);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT);
    buttonState = STGInput_ButtonState_Update(buttonState);
    testCompare(buttonState.state, STGINPUT_BUTTONSTATE_NAME_DOWN);
    
    // Make sure ButtonState functions work properly
    // IsDown
    testAssert(STGInput_ButtonState_Name_IsDown(STGINPUT_BUTTONSTATE_NAME_DOWN));
    testAssert(STGInput_ButtonState_Name_IsDown(STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT));
    testAssert(STGInput_ButtonState_Name_IsDown(STGINPUT_BUTTONSTATE_NAME_PRESSED));
    testAssert(STGInput_ButtonState_Name_IsDown(STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED));
    testAssert(STGInput_ButtonState_Name_IsDown(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK));
    testAssert(STGInput_ButtonState_Name_IsDown(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED));
    // IsPressed
    testAssert(STGInput_ButtonState_Name_IsPressed(STGINPUT_BUTTONSTATE_NAME_PRESSED));
    testAssert(STGInput_ButtonState_Name_IsPressed(STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED));
    testAssert(STGInput_ButtonState_Name_IsPressed(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK));
    testAssert(STGInput_ButtonState_Name_IsPressed(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED));
    // IsPressedOrRepeated
    testAssert(STGInput_ButtonState_Name_IsPressedOrRepeated(STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT));
    testAssert(STGInput_ButtonState_Name_IsPressedOrRepeated(STGINPUT_BUTTONSTATE_NAME_PRESSED));
    testAssert(STGInput_ButtonState_Name_IsPressedOrRepeated(STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED));
    testAssert(STGInput_ButtonState_Name_IsPressedOrRepeated(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK));
    testAssert(STGInput_ButtonState_Name_IsPressedOrRepeated(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED));
    // IsReleased
    testAssert(STGInput_ButtonState_Name_IsReleased(STGINPUT_BUTTONSTATE_NAME_RELEASED));
    // IsDoubleClick
    testAssert(STGInput_ButtonState_Name_IsDoubleClick(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK));
    testAssert(STGInput_ButtonState_Name_IsDoubleClick(STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED));
}
