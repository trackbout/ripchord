#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "KeyboardComponent.h"

//==============================================================================
class InputKeyboardComponent : public KeyboardComponent
{
public:
    //==============================================================================
    InputKeyboardComponent (MainProcess&);
    ~InputKeyboardComponent();

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputKeyboardComponent)
};
