#pragma once

#include "JuceHeader.h"
#include "GlobalState.h"
#include "CurrentPresetState.h"

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
    CurrentPresetState& getCurrentPresetState() { return mCurrentPresetState; }

private:
    //==============================================================================
    MidiBuffer mMidiBuffer;
    GlobalState mGlobalState;
    CurrentPresetState mCurrentPresetState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
