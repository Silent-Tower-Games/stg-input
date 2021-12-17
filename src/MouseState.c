#include <SDL2/SDL.h>
#include "MouseState.h"

void STGInput_MouseState_Poll(STGInput_MouseState* mouse)
{
    if(mouse == NULL)
    {
        return;
    }
    
    Uint32 state = SDL_GetMouseState(&mouse->X, &mouse->Y);
    
    if(!!(state & SDL_BUTTON_LMASK) != STGInput_MouseState_Button_IsDown(mouse, STGINPUT_MOUSEBUTTONS_LEFTCLICK))
    {
        mouse->button[0] = STGInput_ButtonState_Event(
            mouse->button[0],
            state & SDL_BUTTON_LMASK ?
                STGINPUT_BUTTONSTATE_EVENT_DOWN
            :
                STGINPUT_BUTTONSTATE_EVENT_UP
            ,
            STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT
        );
    }
    
    if(!!(state & SDL_BUTTON_MMASK) != STGInput_MouseState_Button_IsDown(mouse, STGINPUT_MOUSEBUTTONS_MIDDLECLICK))
    {
        mouse->button[1] = STGInput_ButtonState_Event(
            mouse->button[1],
            state & SDL_BUTTON_MMASK ?
                STGINPUT_BUTTONSTATE_EVENT_DOWN
            :
                STGINPUT_BUTTONSTATE_EVENT_UP
            ,
            STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT
        );
    }
    
    if(!!(state & SDL_BUTTON_RMASK) != STGInput_MouseState_Button_IsDown(mouse, STGINPUT_MOUSEBUTTONS_RIGHTCLICK))
    {
        mouse->button[2] = STGInput_ButtonState_Event(
            mouse->button[2],
            state & SDL_BUTTON_RMASK ?
                STGINPUT_BUTTONSTATE_EVENT_DOWN
            :
                STGINPUT_BUTTONSTATE_EVENT_UP
            ,
            STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT
        );
    }
}

void STGInput_MouseState_Update(STGInput_MouseState* mouse)
{
    if(mouse == NULL)
    {
        return;
    }
    
    for(int i = 0; i < STGINPUT_MOUSESTATE_BUTTONS_COUNT; i++)
    {
        mouse->button[i] = STGInput_ButtonState_Update(mouse->button[i]);
    }
}

int STGInput_MouseState_ButtonIndex(STGInput_MouseButtons button)
{
    for(int i = 0; i < STGINPUT_MOUSESTATE_BUTTONS_COUNT; i++)
    {
        if(button != STGInput_MouseButtons_List[i])
        {
            continue;
        }
        
        return i;
    }
    
    return -1;
}

STGInput_ButtonState_Name STGInput_MouseState_Button_GetState(STGInput_MouseState* mouse, STGInput_MouseButtons button)
{
    if(mouse == NULL)
    {
        return STGINPUT_BUTTONSTATE_NAME_UP;
    }
    
    int index = STGInput_MouseState_ButtonIndex(button);
    
    if(index < 0 || index >= STGINPUT_MOUSESTATE_BUTTONS_COUNT)
    {
        return STGINPUT_BUTTONSTATE_NAME_UP;
    }
    
    return mouse->button[index].state;
}

char STGInput_MouseState_Button_IsDown(STGInput_MouseState* mouse, STGInput_MouseButtons button)
{
    if(mouse == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsDown(STGInput_MouseState_Button_GetState(mouse, button));
}

char STGInput_MouseState_Button_IsPressed(STGInput_MouseState* mouse, STGInput_MouseButtons button)
{
    if(mouse == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsPressed(STGInput_MouseState_Button_GetState(mouse, button));
}

char STGInput_MouseState_Button_IsPressedOrRepeated(STGInput_MouseState* mouse, STGInput_MouseButtons button)
{
    if(mouse == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_MouseState_Button_GetState(mouse, button));
}

STGInput_MouseButtons STGInput_MouseButtons_List[STGINPUT_MOUSESTATE_BUTTONS_COUNT] = {
    STGINPUT_MOUSEBUTTONS_LEFTCLICK,
    STGINPUT_MOUSEBUTTONS_MIDDLECLICK,
    STGINPUT_MOUSEBUTTONS_RIGHTCLICK,
};
