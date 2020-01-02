#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "KeyboardComponent.h"
#include "DataMessageListener.h"

//==============================================================================
class OutputKeyboardComponent : public KeyboardComponent, public DataMessageListener
{
public:
    //==============================================================================
    OutputKeyboardComponent (MainProcess&);
    ~OutputKeyboardComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void handleMouseDown (const int outputNote);

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;
    void handleModeUpdated (const DataMessage* message);
    void handleEditModeOutputNotes (const DataMessage* message);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputKeyboardComponent)
};
