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
    int getCurrentlyOnTransposeNote();
    juce::Array<int> getCurrentlyOnInputNotes();
    std::map<int, Origin> getCurrentlyOnOutputNotes();

    //==============================================================================
    void setCurrentlyOnTransposeNote (const int inputNote);
    void setCurrentlyOnInputNotes (juce::Array<int> inputNotes);
    void setCurrentlyOnOutputNotes (std::map<int, Origin> outputNotes);

    //==============================================================================
    bool containsOutputNoteTrigger (const int outputNote, const int inputNote);
    const int getOutputNoteTriggerCount (const int outputNote);

private:
    //==============================================================================
    int mCurrentlyOnTransposeNote;
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, Origin> mCurrentlyOnOutputNotes;

    //==============================================================================
    juce::Array<int> getOutputNotesArray (std::map<int, Origin> outputNotes);
    juce::Array<int> getWeightedOutputNotesArray (std::map<int, Origin> outputNotes);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
