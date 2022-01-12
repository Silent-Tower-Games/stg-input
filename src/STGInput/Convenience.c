#include "Convenience.h"

static STGInput* STGInput_Convenience_InputState = NULL;

STGInput* STGInput_Convenience_InputState_Getter()
{
    if(STGInput_Convenience_InputState == NULL)
    {
        STGInput_Convenience_InputState = STGInput_Create();
    }
    
    return STGInput_Convenience_InputState;
}
