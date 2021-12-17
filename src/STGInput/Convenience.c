#include "Convenience.h"

#define STGINPUT_CONVENIENCE
#ifdef STGINPUT_CONVENIENCE

static STGInput* STGInput_Convenience_InputState = NULL;

STGInput* STGInput_Convenience_InputState_Getter()
{
    if(STGInput_Convenience_InputState == NULL)
    {
        STGInput_Convenience_InputState = STGInput_Create();
    }
}

#endif
