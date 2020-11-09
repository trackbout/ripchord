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
    bool isPlaying();
    void setCurrentChannel (int channel);
    void handleSampleCount (int numSamples, double sampleRate, bool isPlaying);

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
    void addSampleCounter (int inputNote);
    void removeSampleCounter (int inputNote);

    //==============================================================================
    void addNoteEventToQueue (NoteEvent noteEvent, int indexInChord, float delayDepth, float delayVariance);
    void removeNoteEventsFromQueue (int inputNote);

    //==============================================================================
    bool timeToSendNextNoteEvent();
    NoteEvent getNextNoteEvent();

    //==============================================================================
    void scrubMidiState (MidiBuffer& midiBuffer);

    //==============================================================================
    void setActiveTransposeNoteIfAllowed (const int inputNote);

private:
    //==============================================================================
    bool mIsPlaying;
    int mCurrentChannel;

    //==============================================================================
    juce::Array<int> mCurrentlyOnInputNotes;
    std::map<int, Origin> mCurrentlyOnOutputNotes;

    //==============================================================================
    std::map<int, int> mSampleCounters;
    std::queue<NoteEvent> mNoteEventQueue;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiState)
};
