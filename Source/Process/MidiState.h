#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"
#include "Midi.h"
#include <queue>

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
    void setInputNoteOn (int inputNote);
    void setInputNoteOff (int inputNote);

    //==============================================================================
    void setOutputNoteOn (int outputNote, juce::Array<int>& triggers);
    void setOutputNoteOff (int outputNote, juce::Array<int>& triggers);

    //==============================================================================
    void setActiveTransposeNoteIfAllowed (const int inputNote);
    void addNoteEventToQueue (NoteEvent noteEvent, int indexInChord, float delayDepth, float delayVariance);
    bool timeToSendNextNoteEvent();
    NoteEvent getNextNoteEvent();

    //==============================================================================
    bool hasStuckNotes();
    juce::Array<int> clearStuckNotes();
    void clearAbortedNoteEvents (int inputNote);

private:
    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, Origin> mCurrentlyOnOutputNotes;
    std::queue<NoteEvent> mNoteEventQueue;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
