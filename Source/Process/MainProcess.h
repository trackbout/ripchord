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
    GlobalState& getGlobalState() { return mGlobalState; }
    ControlsState& getControlsState() { return mControlsState; }
    BrowserState& getBrowserState() { return mBrowserState; }
    PresetState& getPresetState() { return mPresetState; }
    MidiState& getMidiState() { return mMidiState; }

    //==============================================================================
    void handleMidiBuffer (MidiBuffer& midiBuffer, int numSamples, double sampleRate);

    //==============================================================================
    void handlePlayModeMouseUpOnInput (int inputNote);
    void handlePlayModeMouseDownOnInput (int inputNote);

    //==============================================================================
    XmlElement* exportSessionXml();
    void importSessionXml (XmlElement* sessionXml);

private:
    //==============================================================================
    GlobalState mGlobalState;
    ControlsState mControlsState;
    BrowserState mBrowserState;
    PresetState mPresetState;
    MidiState mMidiState;

    //==============================================================================
    MidiBuffer mMouseDownBuffer;
    MidiBuffer mTransformedMidiBuffer;

    //==============================================================================
    int mNumSamples;
    double mSampleRate;
    int mLastChannel;

    //==============================================================================
    void transformMidiBuffer (MidiBuffer& midiBuffer);
    void handleNoteOn (MidiMessage& message, int sampleNumber);
    void handleNoteOff (MidiMessage& message, int sampleNumber);
    void handleNonNote (MidiMessage& message, int sampleNumber);

    //==============================================================================
    void sendOutputNoteOn (NoteEvent noteEvent);
    void sendOutputNoteOff (NoteEvent noteEvent);
    void sendStuckNoteOff (int outputNote);

    //==============================================================================
    void handleNoteEventQueue();

    //==============================================================================
    void handleActiveTransposeNote (int inputNote);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
