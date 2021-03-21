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
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void handleMouseDown (const int outputNote);

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;
    MidiState& mMidiState;

    void handleToggleTheme (const DataMessage* message);
    void handleToggleMode (const DataMessage* message);
    void handlePresetFileNew (const DataMessage* message);
    void handlePresetModified (const DataMessage* message);
    void handlePresetFileLoaded (const DataMessage* message);
    void handleClearStuckNotes (const DataMessage* message);
    void handleEditModeOutputNotes (const DataMessage* message);
    void handleOutputNoteOff (const DataMessage* message);
    void handleOutputNoteOn (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputKeyboardComponent)
};
