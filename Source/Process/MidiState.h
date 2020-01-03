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
    std::map<int, int> getCurrentlyOnOutputNotes();

    //==============================================================================
    void setCurrentlyOnInputNotes (juce::Array<int> inputNotes);
    void setCurrentlyOnOutputNotes (std::map<int, int> outputNotes);

    //==============================================================================
    bool containsCurrentlyOnOutputNote (const int outputNote);
    bool wasOutputNoteTriggeredByInputNote (const int outputNote, const int inputNote);

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    // KEY: output note // VALUE: trigger note
    std::map<int, int> mCurrentlyOnOutputNotes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
