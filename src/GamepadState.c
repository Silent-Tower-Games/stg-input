#include <stdlib.h>
#include "GamepadState.h"

STGInput_GamepadStateList STGInput_GamepadStateList_Create()
{
    STGInput_GamepadStateList list = {
        .allocated = 0,
        .count = 0,
        .states = NULL,
    };
    
    STGInput_GamepadStateList_Expand(&list);
    
    return list;
}

static void STGInput_GamepadStateList_Expand(STGInput_GamepadStateList* list)
{
    list->allocated += STGINPUT_GAMEPADSTATELIST_DEFAULT_COUNT;
    list->states = realloc(list->states, sizeof(STGInput_GamepadState) * list->allocated);
}

void STGInput_GamepadStateList_Add(STGInput_GamepadStateList* list)
{
    if(list->count >= list->allocated)
    {
        STGInput_GamepadStateList_Expand(list);
    }
    
    list->states[list->count];
    
    list->count++;
}
