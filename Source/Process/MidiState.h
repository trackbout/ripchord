#pragma once

#include "JuceHeader.h"
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
    bool containsCurrentlyOnOutputNote (const int outputNote);
    bool containsOutputNoteTrigger (const int outputNote, const int inputNote);
    const int getOutputNoteTriggerCount (const int outputNote, const int inputNote);

    //==============================================================================
    void addTrigger (std::map<int, juce::Array<int>>& outputNotes, const int outputNote, const int inputNote);
    void removeTrigger (std::map<int, juce::Array<int>>& outputNotes, const int outputNote, const int inputNote);

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, juce::Array<int>> mCurrentlyOnOutputNotes;

    //==============================================================================
    juce::Array<int> getOutputNotesArray (std::map<int, juce::Array<int>> outputNotes);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
