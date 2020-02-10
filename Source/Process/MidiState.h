#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"
#include "Midi.h"

//==============================================================================
class MidiState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    MidiState();
    ~MidiState();

    //==============================================================================
    juce::Array<int> getCurrentlyOnInputNotes();
    juce::Array<int> getOutputNoteTriggers (const int outputNote);

    //==============================================================================
    void setCurrentlyOnInputNotes (juce::Array<int> inputNotes);
    void setOutputNoteOn (int outputNote, juce::Array<int>& triggers);
    void setOutputNoteOff (int outputNote, juce::Array<int>& triggers);

    //==============================================================================
    void setActiveTransposeNoteIfAllowed (const int inputNote);
    void addNoteEventToQueu (NoteEvent noteEvent, int indexInChord, float delayDepth, float delayVariance);
    juce::Array<NoteEvent> getNoteEventsToSend();

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, Origin> mCurrentlyOnOutputNotes;
    juce::Array<NoteEvent> mNoteEventQueu;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
