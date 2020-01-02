#pragma once

#include "JuceHeader.h"

//==============================================================================
class MidiState
{
public:
    //==============================================================================
    MidiState();
    ~MidiState();

    //==============================================================================
    juce::Array<int> getCurrentlyOnInputNotes();
    juce::Array<int> getCurrentlyOnOutputNotes();

    //==============================================================================
    void setCurrentlyOnInputNotes (juce::Array<int> inputNotes);
    void setCurrentlyOnOutputNotes (juce::Array<int> outputNotes);

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    juce::Array<int> mCurrentlyOnOutputNotes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
