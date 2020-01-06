#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class MidiState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    MidiState();
    ~MidiState();

    //==============================================================================
    juce::Array<int> getCurrentlyOnInputNotes();
    std::map<int, juce::Array<int>> getCurrentlyOnOutputNotes();

    //==============================================================================
    void setCurrentlyOnInputNotes (juce::Array<int> inputNotes);
    void setCurrentlyOnOutputNotes (std::map<int, juce::Array<int>> outputNotes);

    //==============================================================================
    bool containsOutputNoteTrigger (const int outputNote, const int inputNote);
    const int getOutputNoteTriggerCount (const int outputNote, const int inputNote);

    //==============================================================================
    void handlePlayModeMouseUpOnInput (const int inputNote);
    void handlePlayModeMouseDownOnInput (const int inputNote);

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, juce::Array<int>> mCurrentlyOnOutputNotes;

    //==============================================================================
    juce::Array<int> getOutputNotesArray (std::map<int, juce::Array<int>> outputNotes);
    juce::Array<int> getModifiedOutputNotesArray (std::map<int, juce::Array<int>> outputNotes);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
