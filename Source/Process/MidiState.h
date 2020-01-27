#pragma once

#include "JuceHeader.h"
#include "Midi.h"
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
    std::map<int, Output> getCurrentlyOnOutputNotes();

    //==============================================================================
    void setCurrentlyOnInputNotes (juce::Array<int> inputNotes);
    void setCurrentlyOnOutputNotes (std::map<int, Output> outputNotes);

    //==============================================================================
    bool containsOutputNoteTrigger (const int outputNote, const int inputNote);
    const int getOutputNoteTriggerCount (const int outputNote);

    //==============================================================================
    void setActiveTransposeNoteIfAllowed (const int inputNote);

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, Output> mCurrentlyOnOutputNotes;

    //==============================================================================
    juce::Array<int> getOutputNotesArray (std::map<int, Output> outputNotes);
    juce::Array<int> getWeightedOutputNotesArray (std::map<int, Output> outputNotes);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
