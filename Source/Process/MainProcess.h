#pragma once

#include "JuceHeader.h"
#include "GlobalState.h"
#include "PresetState.h"
#include "BrowserState.h"
#include "MidiState.h"

//==============================================================================
class MainProcess
{
public:
    //==============================================================================
    MainProcess();
    ~MainProcess();

    //==============================================================================
    void handleMidiBuffer (MidiBuffer& midiBuffer, int numberOfSamples);

    //==============================================================================
    void handlePlayModeMouseUpOnInput (int inputNote);
    void handlePlayModeMouseDownOnInput (int inputNote);

    //==============================================================================
    GlobalState& getGlobalState() { return mGlobalState; }
    PresetState& getPresetState() { return mPresetState; }
    BrowserState& getBrowserState() { return mBrowserState; }
    MidiState& getMidiState() { return mMidiState; }

private:
    //==============================================================================
    MidiBuffer mMouseClickBuffer;
    MidiBuffer mTransformedMidiBuffer;

    //==============================================================================
    void transformMidiBuffer (MidiBuffer& midiBuffer);
    void handleNoteOn (MidiMessage& message, int time);
    void handleNoteOff (MidiMessage& message, int time);
    void handleNonNote (MidiMessage& message, int time);

    //==============================================================================
    void noteOnToOutputNotes (int inputNote, int inputChannel, float inputVelocity, int time,
                              int outputNote, std::map<int, juce::Array<int>>& currentlyOnOutputNotes);

    void noteOffToOutputNotes (int inputNote, int inputChannel, float inputVelocity, int time,
                               int outputNote, std::map<int, juce::Array<int>>& currentlyOnOutputNotes);

    //==============================================================================
    GlobalState mGlobalState;
    PresetState mPresetState;
    BrowserState mBrowserState;
    MidiState mMidiState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
