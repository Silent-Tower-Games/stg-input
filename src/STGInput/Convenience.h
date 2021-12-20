#pragma once

#include "STGInput.h"

// This function will always exist
// However, the macros only get defined if you have the STGINPUT_CONVENIENCE define
STGInput* STGInput_Convenience_InputState_Getter();

#ifdef STGINPUT_CONVENIENCE

#define inputEvent(e) STGInput_Event(STGInput_Convenience_InputState_Getter(), e)
#define inputPreframe() STGInput_PreFrame(STGInput_Convenience_InputState_Getter())
#define inputPostframe() STGInput_PostFrame(STGInput_Convenience_InputState_Getter())
#define inputDestroy() STGInput_Destroy(STGInput_Convenience_InputState_Getter())

#define keyboard(state, key) STGInput_KeyboardState_Button_Is ## state(\
    STGInput_Convenience_InputState_Getter()->keyboard,\
    STGINPUT_KEYBOARDKEYS_ ## key\
)

#define gamepadObj(obj, state, button) STGInput_GamepadState_Button_Is ## state(obj, STGINPUT_GAMEPADBUTTONS_ ## button)
#define gamepad(index, state, button) gamepadObj(\
    STGInput_GamepadStateList_FindByIndex(STGInput_Convenience_InputState_Getter()->gamepads, index),\
    state,\
    button\
)
#define rumbleObj(obj) STGInput_GamepadState_GetHaptic(obj)
#define rumble(index) rumbleObj(\
    STGInput_GamepadStateList_FindByIndex(STGInput_Convenience_InputState_Getter()->gamepads, index)\
)

#define mouse(state, button) STGInput_MouseState_Button_Is ## state(\
    STGInput_Convenience_InputState_Getter()->mouse,\
    STGINPUT_MOUSEBUTTONS_ ## button\
)
#define mousePos() STGInput_MouseState_Position(STGInput_Convenience_InputState_Getter()->mouse)
#define scroll() STGInput_MouseState_GetScroll(STGInput_Convenience_InputState_Getter()->mouse)

#endif
