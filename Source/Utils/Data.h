#pragma once

//==============================================================================
namespace Data
{
    //==============================================================================
    static inline bool arrayIntContains (Array<int> array, int integer)
    {
        return std::find (std::begin(array), std::end(array), integer) != std::end(array);
    }
}
