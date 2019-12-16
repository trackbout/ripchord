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
    GlobalState& getGlobalState() { return mGlobalState; }

private:
    //==============================================================================
    GlobalState mGlobalState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
