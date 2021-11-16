#include "ButtonState.h"

int STGInput_ButtonState_Name_IsDown(STGInput_ButtonState_Name buttonState)
{
    switch(buttonState)
    {
        case STGINPUT_BUTTONSTATE_NAME_DOWN:
        case STGINPUT_BUTTONSTATE_NAME_DOWN_REPEAT:
        case STGINPUT_BUTTONSTATE_NAME_PRESSED:
        case STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED:
        {
            return 1;
        }
    }
    
    return 0;
}

int STGInput_ButtonState_Name_IsPressed(STGInput_ButtonState_Name buttonState)
{
    if(
        buttonState == STGINPUT_BUTTONSTATE_NAME_PRESSED
        ||
        buttonState == STGINPUT_BUTTONSTATE_NAME_PRESSED_THEN_RELEASED
    )
    {
        return 1;
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
   }
   
   return 0;
}
