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

    //==============================================================================
    void resized() override;

    //==============================================================================
    void handleMouseUp (const int noteNumber);
    void handleMouseDown (const int noteNumber);

    //==============================================================================
    void handlePlayModeMouseUp (const int noteNumber);
    void handlePlayModeMouseDown (const int noteNumber);

    //==============================================================================
    void handleEditModeMouseUp (const int noteNumber);
    void handleEditModeMouseDown (const int noteNumber);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    CurrentPresetState& mCurrentPresetState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputKeyboardComponent)
};
