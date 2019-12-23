#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "KeyComponent.h"

//==============================================================================
class OutputKeyboardComponent : public Component
{
public:
    //==============================================================================
    OutputKeyboardComponent (MainProcess&);
    ~OutputKeyboardComponent();

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputKeyboardComponent)
};
