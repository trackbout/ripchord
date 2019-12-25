#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class OutputKeyboardState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    OutputKeyboardState();
    ~OutputKeyboardState();

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputKeyboardState)
};
