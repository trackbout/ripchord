#pragma once

#include "JuceHeader.h"
#include "GlobalState.h"
#include "OutputKeyboardState.h"
#include "InputKeyboardState.h"
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
    OutputKeyboardState& getOutputKeyboardState() { return mOutputKeyboardState; }
    InputKeyboardState& getInputKeyboardState() { return mInputKeyboardState; }
    CurrentPresetState& getCurrentPresetState() { return mCurrentPresetState; }

private:
    //==============================================================================
    MidiBuffer mMidiBuffer;

    //==============================================================================
    GlobalState mGlobalState;
    OutputKeyboardState mOutputKeyboardState;
    InputKeyboardState mInputKeyboardState;
    CurrentPresetState mCurrentPresetState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
