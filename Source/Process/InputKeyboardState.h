#pragma once

#include "JuceHeader.h"

//==============================================================================
class InputKeyboardState : public MidiKeyboardState
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
