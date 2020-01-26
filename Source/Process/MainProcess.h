#pragma once

#include "JuceHeader.h"
#include "GlobalState.h"
#include "PresetState.h"
#include "BrowserState.h"
#include "ControlsState.h"
#include "MidiState.h"
#include "Midi.h"

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
    ControlsState& getControlsState() { return mControlsState; }
    BrowserState& getBrowserState() { return mBrowserState; }
    PresetState& getPresetState() { return mPresetState; }
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
    void noteOnToOutputNote (int inputNote, int inputChannel, float inputVelocity, int time,
                             int outputNote, std::map<int, Output>& currentlyOnOutputNotes, bool isChord);

    void noteOffToOutputNote (int inputNote, int inputChannel, float inputVelocity, int time,
                              int outputNote, std::map<int, Output>& currentlyOnOutputNotes, bool isChord);

    //==============================================================================
    void handleActiveTransposeNote (int inputNote);

    //==============================================================================
    GlobalState mGlobalState;
    ControlsState mControlsState;
    BrowserState mBrowserState;
    PresetState mPresetState;
    MidiState mMidiState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
