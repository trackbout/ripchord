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
    void handleMouseUp (const int inputNote);
    void handleMouseDown (const int inputNote);

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    ControlsState& mControlsState;
    PresetState& mPresetState;
    MidiState& mMidiState;

    void handleToggleMode (const DataMessage* message);
    void handlePresetFileNew (const DataMessage* message);
    void handlePresetFileLoaded (const DataMessage* message);
    void handleEditModeInputNote (const DataMessage* message);
    void handleCurrentlyOnInputNotes (const DataMessage* message);
    void handleTransposeBaseChanged (const DataMessage* message);
    void handleToggleTranspose (const DataMessage* message);

    //==============================================================================
    void turnOnTransposeKeys (const int transposeBase);
    void turnOffTransposeKeys (const int transposeBase);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputKeyboardComponent)
};
