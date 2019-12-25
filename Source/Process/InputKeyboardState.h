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

    //==============================================================================
    int getSelectedEditNote();
    void setSelectedEditNote (int noteNumber);

private:
    //==============================================================================
    int mSelectedEditNote;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputKeyboardState)
};
