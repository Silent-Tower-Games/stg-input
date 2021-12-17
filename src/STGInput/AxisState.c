#include "AxisState.h"

STGInput_AxisState STGInput_AxisState_Update(STGInput_AxisState state, Sint16 value)
{
    state.value = value;
    
    if(value > 0)
    {
        state.percentage = (float)value / STGINPUT_AXISSTATE_VALUE_MAX;
    }
    else
    {
        state.percentage = -(float)value / STGINPUT_AXISSTATE_VALUE_MIN;
    }
    
    return state;
}
