#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class InputKeyboardState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    InputKeyboardState();
    ~InputKeyboardState();

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputKeyboardState)
};
