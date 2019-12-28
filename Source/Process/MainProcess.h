#pragma once

#include "JuceHeader.h"
#include "GlobalState.h"
#include "PresetState.h"

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
    GlobalState& getGlobalState() { return mGlobalState; }
    PresetState& getPresetState() { return mPresetState; }

private:
    //==============================================================================
    MidiBuffer mMidiBuffer;

    //==============================================================================
    GlobalState mGlobalState;
    PresetState mPresetState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
