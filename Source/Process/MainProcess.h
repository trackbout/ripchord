#pragma once

#include "JuceHeader.h"
#include "GlobalState.h"

//==============================================================================
class MainProcess
{
public:
    //==============================================================================
    MainProcess();
    ~MainProcess();

    //==============================================================================
    void handleMidiBuffer (MidiBuffer& midiBuffer, int numberOfSamples);
    GlobalState& getGlobalState() { return mGlobalState; }

private:
    //==============================================================================
    MidiBuffer mMidiBuffer;
    GlobalState mGlobalState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
