#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "KeyboardComponent.h"
#include "DataMessageListener.h"

//==============================================================================
class InputKeyboardComponent : public KeyboardComponent, public DataMessageListener
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

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;
    void handleSelectedEditNote (const DataMessage* message);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputKeyboardComponent)
};
