#pragma once

#include "JuceHeader.h"

//==============================================================================
class OutputKeyboardState : public MidiKeyboardState
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
