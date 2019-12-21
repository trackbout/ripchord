#include "CurrentPresetState.h"

//==============================================================================
CurrentPresetState::CurrentPresetState()
{
}

CurrentPresetState::~CurrentPresetState()
{
}

//==============================================================================
String CurrentPresetState::getPresetName()
{
    return mPresetName;
}

void CurrentPresetState::setPresetName (String inName)
{
    mPresetName = inName;
}
