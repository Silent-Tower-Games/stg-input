#include "ButtonState.h"

STGInput_ButtonState STGInput_ButtonState_Event(
    STGInput_ButtonState buttonState,
    char down,
    char repeat
)
{
    switch(down)
    {
        case 1:
        {
            if(repeat)
            {
                buttonState.state = STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT;
            }
            else if(buttonState.lastPressed > 0)
            {
                buttonState.state = STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK;
                
                buttonState.lastPressed = 0;
            }
            else
            {
                buttonState.state = STGINPUT_BUTTONSTATE_NAME_PRESSED;
            }
        } break;
        
        case 0:
        {
            if(buttonState.state == STGINPUT_BUTTONSTATE_NAME_PRESSED)
            {
                buttonState.state = STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED;
            }
            else if(buttonState.state == STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK)
            {
                buttonState.state = STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED;
            }
            else
            {
                buttonState.state = STGINPUT_BUTTONSTATE_NAME_RELEASED;
            }
        } break;
    }
    
    return buttonState;
}

STGInput_ButtonState STGInput_ButtonState_Update(STGInput_ButtonState buttonState)
{
    if(
        buttonState.state == STGINPUT_BUTTONSTATE_NAME_PRESSED
        ||
        buttonState.state == STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED
    )
    {
        // TODO: This number is magical :) should probably be swapped out for a compiler flag or something
        buttonState.lastPressed = 30;
    }
    else
    {
        buttonState.lastPressed--;
    }
    
    switch(buttonState.state)
    {
        case STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT:
        {
            buttonState.state = STGINPUT_BUTTONSTATE_NAME_DOWN;
        } break;
        
        case STGINPUT_BUTTONSTATE_NAME_PRESSED:
        {
            buttonState.state = STGINPUT_BUTTONSTATE_NAME_DOWN;
        } break;
        
        case STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED:
        {
            buttonState.state = STGINPUT_BUTTONSTATE_NAME_RELEASED;
        } break;
        
        case STGINPUT_BUTTONSTATE_NAME_RELEASED:
        {
            buttonState.state = STGINPUT_BUTTONSTATE_NAME_UP;
        } break;
        
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK:
        {
            buttonState.state = STGINPUT_BUTTONSTATE_NAME_DOWN;
        } break;
        
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED:
        {
            buttonState.state = STGINPUT_BUTTONSTATE_NAME_RELEASED;
        } break;
    }
    
    return buttonState;
}

char STGInput_ButtonState_Name_IsDown(STGInput_ButtonState_Name buttonState)
{
    switch(buttonState)
    {
        case STGINPUT_BUTTONSTATE_NAME_DOWN:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT:
        case STGINPUT_BUTTONSTATE_NAME_PRESSED:
        case STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED:
        {
            return 1;
        }
    }
    
    return 0;
}

char STGInput_ButtonState_Name_IsPressed(STGInput_ButtonState_Name buttonState)
{
    switch(buttonState)
    {
        case STGINPUT_BUTTONSTATE_NAME_PRESSED:
        case STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED:
        {
            return 1;
        }
    }
    
    return 0;
}

char STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_ButtonState_Name buttonState)
{
    switch(buttonState)
    {
        case STGINPUT_BUTTONSTATE_NAME_PRESSED:
        case STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT:
        {
            return 1;
        }
    }
    
    return 0;
}

char* STGInput_ButtonState_Name_ToString(STGInput_ButtonState_Name buttonState)
{
    switch(buttonState)
    {
        case STGINPUT_BUTTONSTATE_NAME_INVALID:
            return "Invalid";
        case STGINPUT_BUTTONSTATE_NAME_UP:
            return "Up";
        case STGINPUT_BUTTONSTATE_NAME_DOWN:
            return "Down";
        case STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT:
            return "Repeat";
        case STGINPUT_BUTTONSTATE_NAME_PRESSED:
            return "Pressed";
        case STGINPUT_BUTTONSTATE_NAME_RELEASED:
            return "Released";
        case STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED:
            return "Pressed Then Released";
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK:
            return "Double Clicked";
        case STGINPUT_BUTTONSTATE_NAME_DOWN_DOUBLECLICK_THEN_RELEASED:
            return "Double Clicked Then Released";
   }
   
   return "---";
}
