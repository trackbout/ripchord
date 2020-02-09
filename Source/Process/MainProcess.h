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
    void handleMidiBuffer (MidiBuffer& midiBuffer);

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
    MidiBuffer mMouseClickBuffer;
    MidiBuffer mTransformedMidiBuffer;

    //==============================================================================
    void transformMidiBuffer (MidiBuffer& midiBuffer);
    void handleNoteOn (MidiMessage& message, int sampleNumber);
    void handleNoteOff (MidiMessage& message, int sampleNumber);
    void handleNonNote (MidiMessage& message, int sampleNumber);

    //==============================================================================
    void sendOutputNoteOn (NoteEvent noteEvent, std::map<int, Origin>& currentlyOnOutputNotes);
    void sendOutputNoteOff (NoteEvent noteEvent, std::map<int, Origin>& currentlyOnOutputNotes);

    //==============================================================================
    void handleActiveTransposeNote (int inputNote);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
