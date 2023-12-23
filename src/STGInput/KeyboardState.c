#include <SDL2/SDL.h>
#include "KeyboardState.h"

typedef struct STGInput_KeyboardState
{
    STGInput_ButtonState button[STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT];
} STGInput_KeyboardState;

static const SDL_KeyCode SDL_KeyCodes_To_STGInput_KeyboardKeys_List[STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT];
static const STGInput_KeyboardKeys STGInput_KeyboardKeys_To_SDL_KeyCodes_List[STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT];

STGInput_KeyboardState* STGInput_KeyboardState_Create()
{
    STGInput_KeyboardState* keyboard = calloc(1, sizeof(STGInput_KeyboardState));
    
    return keyboard;
}

static int STGInput_KeyboardState_SDL_KeyCode_Index(SDL_KeyCode code)
{
    // TODO: Is there a faster way to do this? This is O(n)
    
    for(int i = 0; i < STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT; i++)
    {
        if(code == SDL_KeyCodes_To_STGInput_KeyboardKeys_List[i])
        {
            return i;
        }
    }
    
    return -1;
}

static int STGInput_KeyboardState_KeyboardKeys_Index(STGInput_KeyboardKeys key)
{
    // TODO: Is there a faster way to do this? This is O(n)
    
    for(int i = 0; i < STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT; i++)
    {
        if(key == STGInput_KeyboardKeys_To_SDL_KeyCodes_List[i])
        {
            return i;
        }
    }
    
    return -1;
}

void STGInput_KeyboardState_Event(STGInput_KeyboardState* keyboard, SDL_Event event)
{
    if(keyboard == NULL)
    {
        return;
    }
    
    int index = STGInput_KeyboardState_SDL_KeyCode_Index(event.key.keysym.sym);
    
    if(index < 0 || index >= STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT)
    {
        return;
    }
    
    switch(event.type)
    {
        case SDL_KEYDOWN:
        {
            keyboard->button[index] = STGInput_ButtonState_Event(
                keyboard->button[index],
                STGINPUT_BUTTONSTATE_EVENT_DOWN,
                event.key.repeat
            );
        } break;
        
        case SDL_KEYUP:
        {
            keyboard->button[index] = STGInput_ButtonState_Event(
                keyboard->button[index],
                STGINPUT_BUTTONSTATE_EVENT_UP,
                STGINPUT_BUTTONSTATE_EVENT_NOTREPEAT
            );
        } break;
    }
}

void STGInput_KeyboardState_Update(STGInput_KeyboardState* keyboard)
{
    if(keyboard == NULL)
    {
        return;
    }
    
    for(int i = 0; i < STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT; i++)
    {
        keyboard->button[i] = STGInput_ButtonState_Update(keyboard->button[i]);
    }
}

STGInput_ButtonState_Name STGInput_KeyboardState_Button_GetState(STGInput_KeyboardState* keyboard, STGInput_KeyboardKeys key)
{
    if(keyboard == NULL)
    {
        return 0;
    }
    
    int index = STGInput_KeyboardState_KeyboardKeys_Index(key);
    
    if(index < 0 || index >= STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT)
    {
        return STGINPUT_BUTTONSTATE_NAME_UP;
    }
    
    return keyboard->button[index].state;
}

char STGInput_KeyboardState_Button_IsDown(STGInput_KeyboardState* keyboard, STGInput_KeyboardKeys key)
{
    if(keyboard == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsDown(STGInput_KeyboardState_Button_GetState(keyboard, key));
}

char STGInput_KeyboardState_Button_IsPressed(STGInput_KeyboardState* keyboard, STGInput_KeyboardKeys key)
{
    if(keyboard == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsPressed(STGInput_KeyboardState_Button_GetState(keyboard, key));
}

char STGInput_KeyboardState_Button_IsPressedOrRepeated(STGInput_KeyboardState* keyboard, STGInput_KeyboardKeys key)
{
    if(keyboard == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsPressedOrRepeated(STGInput_KeyboardState_Button_GetState(keyboard, key));
}

char STGInput_KeyboardState_Button_IsReleased(STGInput_KeyboardState* keyboard, STGInput_KeyboardKeys key)
{
    if(keyboard == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsReleased(STGInput_KeyboardState_Button_GetState(keyboard, key));
}

char STGInput_KeyboardState_Button_IsDoubleClick(STGInput_KeyboardState* keyboard, STGInput_KeyboardKeys key)
{
    if(keyboard == NULL)
    {
        return 0;
    }
    
    return STGInput_ButtonState_Name_IsDoubleClick(STGInput_KeyboardState_Button_GetState(keyboard, key));
}

static const SDL_KeyCode SDL_KeyCodes_To_STGInput_KeyboardKeys_List[STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT] = {
    SDLK_UNKNOWN,
    SDLK_RETURN,
    SDLK_ESCAPE,
    SDLK_BACKSPACE,
    SDLK_TAB,
    SDLK_SPACE,
    SDLK_EXCLAIM,
    SDLK_QUOTEDBL,
    SDLK_HASH,
    SDLK_PERCENT,
    SDLK_DOLLAR,
    SDLK_AMPERSAND,
    SDLK_QUOTE,
    SDLK_LEFTPAREN,
    SDLK_RIGHTPAREN,
    SDLK_ASTERISK,
    SDLK_PLUS,
    SDLK_COMMA,
    SDLK_MINUS,
    SDLK_PERIOD,
    SDLK_SLASH,
    SDLK_0,
    SDLK_1,
    SDLK_2,
    SDLK_3,
    SDLK_4,
    SDLK_5,
    SDLK_6,
    SDLK_7,
    SDLK_8,
    SDLK_9,
    SDLK_COLON,
    SDLK_SEMICOLON,
    SDLK_LESS,
    SDLK_EQUALS,
    SDLK_GREATER,
    SDLK_QUESTION,
    SDLK_AT,
    SDLK_LEFTBRACKET,
    SDLK_BACKSLASH,
    SDLK_RIGHTBRACKET,
    SDLK_CARET,
    SDLK_UNDERSCORE,
    SDLK_BACKQUOTE,
    SDLK_a,
    SDLK_b,
    SDLK_c,
    SDLK_d,
    SDLK_e,
    SDLK_f,
    SDLK_g,
    SDLK_h,
    SDLK_i,
    SDLK_j,
    SDLK_k,
    SDLK_l,
    SDLK_m,
    SDLK_n,
    SDLK_o,
    SDLK_p,
    SDLK_q,
    SDLK_r,
    SDLK_s,
    SDLK_t,
    SDLK_u,
    SDLK_v,
    SDLK_w,
    SDLK_x,
    SDLK_y,
    SDLK_z,
    SDLK_CAPSLOCK,
    SDLK_F1,
    SDLK_F2,
    SDLK_F3,
    SDLK_F4,
    SDLK_F5,
    SDLK_F6,
    SDLK_F7,
    SDLK_F8,
    SDLK_F9,
    SDLK_F10,
    SDLK_F11,
    SDLK_F12,
    SDLK_PRINTSCREEN,
    SDLK_SCROLLLOCK,
    SDLK_PAUSE,
    SDLK_INSERT,
    SDLK_HOME,
    SDLK_PAGEUP,
    SDLK_DELETE,
    SDLK_END,
    SDLK_PAGEDOWN,
    SDLK_RIGHT,
    SDLK_LEFT,
    SDLK_DOWN,
    SDLK_UP,
    SDLK_NUMLOCKCLEAR,
    SDLK_KP_DIVIDE,
    SDLK_KP_MULTIPLY,
    SDLK_KP_MINUS,
    SDLK_KP_PLUS,
    SDLK_KP_ENTER,
    SDLK_KP_1,
    SDLK_KP_2,
    SDLK_KP_3,
    SDLK_KP_4,
    SDLK_KP_5,
    SDLK_KP_6,
    SDLK_KP_7,
    SDLK_KP_8,
    SDLK_KP_9,
    SDLK_KP_0,
    SDLK_KP_PERIOD,
    SDLK_APPLICATION,
    SDLK_POWER,
    SDLK_KP_EQUALS,
    SDLK_F13,
    SDLK_F14,
    SDLK_F15,
    SDLK_F16,
    SDLK_F17,
    SDLK_F18,
    SDLK_F19,
    SDLK_F20,
    SDLK_F21,
    SDLK_F22,
    SDLK_F23,
    SDLK_F24,
    SDLK_EXECUTE,
    SDLK_HELP,
    SDLK_MENU,
    SDLK_SELECT,
    SDLK_STOP,
    SDLK_AGAIN,
    SDLK_UNDO,
    SDLK_CUT,
    SDLK_COPY,
    SDLK_PASTE,
    SDLK_FIND,
    SDLK_MUTE,
    SDLK_VOLUMEUP,
    SDLK_VOLUMEDOWN,
    SDLK_KP_COMMA,
    SDLK_KP_EQUALSAS400,
    SDLK_ALTERASE,
    SDLK_SYSREQ,
    SDLK_CANCEL,
    SDLK_CLEAR,
    SDLK_PRIOR,
    SDLK_RETURN2,
    SDLK_SEPARATOR,
    SDLK_OUT,
    SDLK_OPER,
    SDLK_CLEARAGAIN,
    SDLK_CRSEL,
    SDLK_EXSEL,
    SDLK_KP_00,
    SDLK_KP_000,
    SDLK_THOUSANDSSEPARATOR,
    SDLK_DECIMALSEPARATOR,
    SDLK_CURRENCYUNIT,
    SDLK_CURRENCYSUBUNIT,
    SDLK_KP_LEFTPAREN,
    SDLK_KP_RIGHTPAREN,
    SDLK_KP_LEFTBRACE,
    SDLK_KP_RIGHTBRACE,
    SDLK_KP_TAB,
    SDLK_KP_BACKSPACE,
    SDLK_KP_A,
    SDLK_KP_B,
    SDLK_KP_C,
    SDLK_KP_D,
    SDLK_KP_E,
    SDLK_KP_F,
    SDLK_KP_XOR,
    SDLK_KP_POWER,
    SDLK_KP_PERCENT,
    SDLK_KP_LESS,
    SDLK_KP_GREATER,
    SDLK_KP_AMPERSAND,
    SDLK_KP_DBLAMPERSAND,
    SDLK_KP_VERTICALBAR,
    SDLK_KP_DBLVERTICALBAR,
    SDLK_KP_COLON,
    SDLK_KP_HASH,
    SDLK_KP_SPACE,
    SDLK_KP_AT,
    SDLK_KP_EXCLAM,
    SDLK_KP_MEMSTORE,
    SDLK_KP_MEMRECALL,
    SDLK_KP_MEMCLEAR,
    SDLK_KP_MEMADD,
    SDLK_KP_MEMSUBTRACT,
    SDLK_KP_MEMMULTIPLY,
    SDLK_KP_MEMDIVIDE,
    SDLK_KP_PLUSMINUS,
    SDLK_KP_CLEAR,
    SDLK_KP_CLEARENTRY,
    SDLK_KP_BINARY,
    SDLK_KP_OCTAL,
    SDLK_KP_DECIMAL,
    SDLK_KP_HEXADECIMAL,
    SDLK_LCTRL,
    SDLK_LSHIFT,
    SDLK_LALT,
    SDLK_LGUI,
    SDLK_RCTRL,
    SDLK_RSHIFT,
    SDLK_RALT,
    SDLK_RGUI,
    SDLK_MODE,
    SDLK_AUDIONEXT,
    SDLK_AUDIOPREV,
    SDLK_AUDIOSTOP,
    SDLK_AUDIOPLAY,
    SDLK_AUDIOMUTE,
    SDLK_MEDIASELECT,
    SDLK_WWW,
    SDLK_MAIL,
    SDLK_CALCULATOR,
    SDLK_COMPUTER,
    SDLK_AC_SEARCH,
    SDLK_AC_HOME,
    SDLK_AC_BACK,
    SDLK_AC_FORWARD,
    SDLK_AC_STOP,
    SDLK_AC_REFRESH,
    SDLK_AC_BOOKMARKS,
    SDLK_BRIGHTNESSDOWN,
    SDLK_BRIGHTNESSUP,
    SDLK_DISPLAYSWITCH,
    SDLK_KBDILLUMTOGGLE,
    SDLK_KBDILLUMDOWN,
    SDLK_KBDILLUMUP,
    SDLK_EJECT,
    SDLK_SLEEP,
    SDLK_APP1,
    SDLK_APP2,
    SDLK_AUDIOREWIND,
    SDLK_AUDIOFASTFORWARD,
};

static const STGInput_KeyboardKeys STGInput_KeyboardKeys_To_SDL_KeyCodes_List[STGINPUT_KEYBOARDSTATE_KEYCODES_COUNT] = {
    STGINPUT_KEYBOARDKEYS_UNKNOWN,
    STGINPUT_KEYBOARDKEYS_RETURN,
    STGINPUT_KEYBOARDKEYS_ESCAPE,
    STGINPUT_KEYBOARDKEYS_BACKSPACE,
    STGINPUT_KEYBOARDKEYS_TAB,
    STGINPUT_KEYBOARDKEYS_SPACE,
    STGINPUT_KEYBOARDKEYS_EXCLAIM,
    STGINPUT_KEYBOARDKEYS_QUOTEDBL,
    STGINPUT_KEYBOARDKEYS_HASH,
    STGINPUT_KEYBOARDKEYS_PERCENT,
    STGINPUT_KEYBOARDKEYS_DOLLAR,
    STGINPUT_KEYBOARDKEYS_AMPERSAND,
    STGINPUT_KEYBOARDKEYS_QUOTE,
    STGINPUT_KEYBOARDKEYS_LEFTPAREN,
    STGINPUT_KEYBOARDKEYS_RIGHTPAREN,
    STGINPUT_KEYBOARDKEYS_ASTERISK,
    STGINPUT_KEYBOARDKEYS_PLUS,
    STGINPUT_KEYBOARDKEYS_COMMA,
    STGINPUT_KEYBOARDKEYS_MINUS,
    STGINPUT_KEYBOARDKEYS_PERIOD,
    STGINPUT_KEYBOARDKEYS_SLASH,
    STGINPUT_KEYBOARDKEYS_0,
    STGINPUT_KEYBOARDKEYS_1,
    STGINPUT_KEYBOARDKEYS_2,
    STGINPUT_KEYBOARDKEYS_3,
    STGINPUT_KEYBOARDKEYS_4,
    STGINPUT_KEYBOARDKEYS_5,
    STGINPUT_KEYBOARDKEYS_6,
    STGINPUT_KEYBOARDKEYS_7,
    STGINPUT_KEYBOARDKEYS_8,
    STGINPUT_KEYBOARDKEYS_9,
    STGINPUT_KEYBOARDKEYS_COLON,
    STGINPUT_KEYBOARDKEYS_SEMICOLON,
    STGINPUT_KEYBOARDKEYS_LESS,
    STGINPUT_KEYBOARDKEYS_EQUALS,
    STGINPUT_KEYBOARDKEYS_GREATER,
    STGINPUT_KEYBOARDKEYS_QUESTION,
    STGINPUT_KEYBOARDKEYS_AT,
    STGINPUT_KEYBOARDKEYS_LEFTBRACKET,
    STGINPUT_KEYBOARDKEYS_BACKSLASH,
    STGINPUT_KEYBOARDKEYS_RIGHTBRACKET,
    STGINPUT_KEYBOARDKEYS_CARET,
    STGINPUT_KEYBOARDKEYS_UNDERSCORE,
    STGINPUT_KEYBOARDKEYS_BACKQUOTE,
    STGINPUT_KEYBOARDKEYS_a,
    STGINPUT_KEYBOARDKEYS_b,
    STGINPUT_KEYBOARDKEYS_c,
    STGINPUT_KEYBOARDKEYS_d,
    STGINPUT_KEYBOARDKEYS_e,
    STGINPUT_KEYBOARDKEYS_f,
    STGINPUT_KEYBOARDKEYS_g,
    STGINPUT_KEYBOARDKEYS_h,
    STGINPUT_KEYBOARDKEYS_i,
    STGINPUT_KEYBOARDKEYS_j,
    STGINPUT_KEYBOARDKEYS_k,
    STGINPUT_KEYBOARDKEYS_l,
    STGINPUT_KEYBOARDKEYS_m,
    STGINPUT_KEYBOARDKEYS_n,
    STGINPUT_KEYBOARDKEYS_o,
    STGINPUT_KEYBOARDKEYS_p,
    STGINPUT_KEYBOARDKEYS_q,
    STGINPUT_KEYBOARDKEYS_r,
    STGINPUT_KEYBOARDKEYS_s,
    STGINPUT_KEYBOARDKEYS_t,
    STGINPUT_KEYBOARDKEYS_u,
    STGINPUT_KEYBOARDKEYS_v,
    STGINPUT_KEYBOARDKEYS_w,
    STGINPUT_KEYBOARDKEYS_x,
    STGINPUT_KEYBOARDKEYS_y,
    STGINPUT_KEYBOARDKEYS_z,
    STGINPUT_KEYBOARDKEYS_CAPSLOCK,
    STGINPUT_KEYBOARDKEYS_F1,
    STGINPUT_KEYBOARDKEYS_F2,
    STGINPUT_KEYBOARDKEYS_F3,
    STGINPUT_KEYBOARDKEYS_F4,
    STGINPUT_KEYBOARDKEYS_F5,
    STGINPUT_KEYBOARDKEYS_F6,
    STGINPUT_KEYBOARDKEYS_F7,
    STGINPUT_KEYBOARDKEYS_F8,
    STGINPUT_KEYBOARDKEYS_F9,
    STGINPUT_KEYBOARDKEYS_F10,
    STGINPUT_KEYBOARDKEYS_F11,
    STGINPUT_KEYBOARDKEYS_F12,
    STGINPUT_KEYBOARDKEYS_PRINTSCREEN,
    STGINPUT_KEYBOARDKEYS_SCROLLLOCK,
    STGINPUT_KEYBOARDKEYS_PAUSE,
    STGINPUT_KEYBOARDKEYS_INSERT,
    STGINPUT_KEYBOARDKEYS_HOME,
    STGINPUT_KEYBOARDKEYS_PAGEUP,
    STGINPUT_KEYBOARDKEYS_DELETE,
    STGINPUT_KEYBOARDKEYS_END,
    STGINPUT_KEYBOARDKEYS_PAGEDOWN,
    STGINPUT_KEYBOARDKEYS_RIGHT,
    STGINPUT_KEYBOARDKEYS_LEFT,
    STGINPUT_KEYBOARDKEYS_DOWN,
    STGINPUT_KEYBOARDKEYS_UP,
    STGINPUT_KEYBOARDKEYS_NUMLOCKCLEAR,
    STGINPUT_KEYBOARDKEYS_KP_DIVIDE,
    STGINPUT_KEYBOARDKEYS_KP_MULTIPLY,
    STGINPUT_KEYBOARDKEYS_KP_MINUS,
    STGINPUT_KEYBOARDKEYS_KP_PLUS,
    STGINPUT_KEYBOARDKEYS_KP_ENTER,
    STGINPUT_KEYBOARDKEYS_KP_1,
    STGINPUT_KEYBOARDKEYS_KP_2,
    STGINPUT_KEYBOARDKEYS_KP_3,
    STGINPUT_KEYBOARDKEYS_KP_4,
    STGINPUT_KEYBOARDKEYS_KP_5,
    STGINPUT_KEYBOARDKEYS_KP_6,
    STGINPUT_KEYBOARDKEYS_KP_7,
    STGINPUT_KEYBOARDKEYS_KP_8,
    STGINPUT_KEYBOARDKEYS_KP_9,
    STGINPUT_KEYBOARDKEYS_KP_0,
    STGINPUT_KEYBOARDKEYS_KP_PERIOD,
    STGINPUT_KEYBOARDKEYS_APPLICATION,
    STGINPUT_KEYBOARDKEYS_POWER,
    STGINPUT_KEYBOARDKEYS_KP_EQUALS,
    STGINPUT_KEYBOARDKEYS_F13,
    STGINPUT_KEYBOARDKEYS_F14,
    STGINPUT_KEYBOARDKEYS_F15,
    STGINPUT_KEYBOARDKEYS_F16,
    STGINPUT_KEYBOARDKEYS_F17,
    STGINPUT_KEYBOARDKEYS_F18,
    STGINPUT_KEYBOARDKEYS_F19,
    STGINPUT_KEYBOARDKEYS_F20,
    STGINPUT_KEYBOARDKEYS_F21,
    STGINPUT_KEYBOARDKEYS_F22,
    STGINPUT_KEYBOARDKEYS_F23,
    STGINPUT_KEYBOARDKEYS_F24,
    STGINPUT_KEYBOARDKEYS_EXECUTE,
    STGINPUT_KEYBOARDKEYS_HELP,
    STGINPUT_KEYBOARDKEYS_MENU,
    STGINPUT_KEYBOARDKEYS_SELECT,
    STGINPUT_KEYBOARDKEYS_STOP,
    STGINPUT_KEYBOARDKEYS_AGAIN,
    STGINPUT_KEYBOARDKEYS_UNDO,
    STGINPUT_KEYBOARDKEYS_CUT,
    STGINPUT_KEYBOARDKEYS_COPY,
    STGINPUT_KEYBOARDKEYS_PASTE,
    STGINPUT_KEYBOARDKEYS_FIND,
    STGINPUT_KEYBOARDKEYS_MUTE,
    STGINPUT_KEYBOARDKEYS_VOLUMEUP,
    STGINPUT_KEYBOARDKEYS_VOLUMEDOWN,
    STGINPUT_KEYBOARDKEYS_KP_COMMA,
    STGINPUT_KEYBOARDKEYS_KP_EQUALSAS400,
    STGINPUT_KEYBOARDKEYS_ALTERASE,
    STGINPUT_KEYBOARDKEYS_SYSREQ,
    STGINPUT_KEYBOARDKEYS_CANCEL,
    STGINPUT_KEYBOARDKEYS_CLEAR,
    STGINPUT_KEYBOARDKEYS_PRIOR,
    STGINPUT_KEYBOARDKEYS_RETURN2,
    STGINPUT_KEYBOARDKEYS_SEPARATOR,
    STGINPUT_KEYBOARDKEYS_OUT,
    STGINPUT_KEYBOARDKEYS_OPER,
    STGINPUT_KEYBOARDKEYS_CLEARAGAIN,
    STGINPUT_KEYBOARDKEYS_CRSEL,
    STGINPUT_KEYBOARDKEYS_EXSEL,
    STGINPUT_KEYBOARDKEYS_KP_00,
    STGINPUT_KEYBOARDKEYS_KP_000,
    STGINPUT_KEYBOARDKEYS_THOUSANDSSEPARATOR,
    STGINPUT_KEYBOARDKEYS_DECIMALSEPARATOR,
    STGINPUT_KEYBOARDKEYS_CURRENCYUNIT,
    STGINPUT_KEYBOARDKEYS_CURRENCYSUBUNIT,
    STGINPUT_KEYBOARDKEYS_KP_LEFTPAREN,
    STGINPUT_KEYBOARDKEYS_KP_RIGHTPAREN,
    STGINPUT_KEYBOARDKEYS_KP_LEFTBRACE,
    STGINPUT_KEYBOARDKEYS_KP_RIGHTBRACE,
    STGINPUT_KEYBOARDKEYS_KP_TAB,
    STGINPUT_KEYBOARDKEYS_KP_BACKSPACE,
    STGINPUT_KEYBOARDKEYS_KP_A,
    STGINPUT_KEYBOARDKEYS_KP_B,
    STGINPUT_KEYBOARDKEYS_KP_C,
    STGINPUT_KEYBOARDKEYS_KP_D,
    STGINPUT_KEYBOARDKEYS_KP_E,
    STGINPUT_KEYBOARDKEYS_KP_F,
    STGINPUT_KEYBOARDKEYS_KP_XOR,
    STGINPUT_KEYBOARDKEYS_KP_POWER,
    STGINPUT_KEYBOARDKEYS_KP_PERCENT,
    STGINPUT_KEYBOARDKEYS_KP_LESS,
    STGINPUT_KEYBOARDKEYS_KP_GREATER,
    STGINPUT_KEYBOARDKEYS_KP_AMPERSAND,
    STGINPUT_KEYBOARDKEYS_KP_DBLAMPERSAND,
    STGINPUT_KEYBOARDKEYS_KP_VERTICALBAR,
    STGINPUT_KEYBOARDKEYS_KP_DBLVERTICALBAR,
    STGINPUT_KEYBOARDKEYS_KP_COLON,
    STGINPUT_KEYBOARDKEYS_KP_HASH,
    STGINPUT_KEYBOARDKEYS_KP_SPACE,
    STGINPUT_KEYBOARDKEYS_KP_AT,
    STGINPUT_KEYBOARDKEYS_KP_EXCLAM,
    STGINPUT_KEYBOARDKEYS_KP_MEMSTORE,
    STGINPUT_KEYBOARDKEYS_KP_MEMRECALL,
    STGINPUT_KEYBOARDKEYS_KP_MEMCLEAR,
    STGINPUT_KEYBOARDKEYS_KP_MEMADD,
    STGINPUT_KEYBOARDKEYS_KP_MEMSUBTRACT,
    STGINPUT_KEYBOARDKEYS_KP_MEMMULTIPLY,
    STGINPUT_KEYBOARDKEYS_KP_MEMDIVIDE,
    STGINPUT_KEYBOARDKEYS_KP_PLUSMINUS,
    STGINPUT_KEYBOARDKEYS_KP_CLEAR,
    STGINPUT_KEYBOARDKEYS_KP_CLEARENTRY,
    STGINPUT_KEYBOARDKEYS_KP_BINARY,
    STGINPUT_KEYBOARDKEYS_KP_OCTAL,
    STGINPUT_KEYBOARDKEYS_KP_DECIMAL,
    STGINPUT_KEYBOARDKEYS_KP_HEXADECIMAL,
    STGINPUT_KEYBOARDKEYS_LCTRL,
    STGINPUT_KEYBOARDKEYS_LSHIFT,
    STGINPUT_KEYBOARDKEYS_LALT,
    STGINPUT_KEYBOARDKEYS_LGUI,
    STGINPUT_KEYBOARDKEYS_RCTRL,
    STGINPUT_KEYBOARDKEYS_RSHIFT,
    STGINPUT_KEYBOARDKEYS_RALT,
    STGINPUT_KEYBOARDKEYS_RGUI,
    STGINPUT_KEYBOARDKEYS_MODE,
    STGINPUT_KEYBOARDKEYS_AUDIONEXT,
    STGINPUT_KEYBOARDKEYS_AUDIOPREV,
    STGINPUT_KEYBOARDKEYS_AUDIOSTOP,
    STGINPUT_KEYBOARDKEYS_AUDIOPLAY,
    STGINPUT_KEYBOARDKEYS_AUDIOMUTE,
    STGINPUT_KEYBOARDKEYS_MEDIASELECT,
    STGINPUT_KEYBOARDKEYS_WWW,
    STGINPUT_KEYBOARDKEYS_MAIL,
    STGINPUT_KEYBOARDKEYS_CALCULATOR,
    STGINPUT_KEYBOARDKEYS_COMPUTER,
    STGINPUT_KEYBOARDKEYS_AC_SEARCH,
    STGINPUT_KEYBOARDKEYS_AC_HOME,
    STGINPUT_KEYBOARDKEYS_AC_BACK,
    STGINPUT_KEYBOARDKEYS_AC_FORWARD,
    STGINPUT_KEYBOARDKEYS_AC_STOP,
    STGINPUT_KEYBOARDKEYS_AC_REFRESH,
    STGINPUT_KEYBOARDKEYS_AC_BOOKMARKS,
    STGINPUT_KEYBOARDKEYS_BRIGHTNESSDOWN,
    STGINPUT_KEYBOARDKEYS_BRIGHTNESSUP,
    STGINPUT_KEYBOARDKEYS_DISPLAYSWITCH,
    STGINPUT_KEYBOARDKEYS_KBDILLUMTOGGLE,
    STGINPUT_KEYBOARDKEYS_KBDILLUMDOWN,
    STGINPUT_KEYBOARDKEYS_KBDILLUMUP,
    STGINPUT_KEYBOARDKEYS_EJECT,
    STGINPUT_KEYBOARDKEYS_SLEEP,
    STGINPUT_KEYBOARDKEYS_APP1,
    STGINPUT_KEYBOARDKEYS_APP2,
    STGINPUT_KEYBOARDKEYS_AUDIOREWIND,
    STGINPUT_KEYBOARDKEYS_AUDIOFASTFORWARD,
};
