#pragma once

#include "JuceHeader.h"
#include "Styles.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class ChordNameComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    ChordNameComponent (MainProcess&);
    ~ChordNameComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;
    MidiState& mMidiState;

    TextLabel mChordNameLabel;
    TextInput mChordNameInput;

    void handleModeUpdated (const DataMessage* message);
    void handlePresetFileNew (const DataMessage* message);
    void handlePresetFileLoaded (const DataMessage* message);
    void handleEditModeInputNote (const DataMessage* message);
    void handleEditModeOutputNotes (const DataMessage* message);
    void handleCurrentlyOnInputNotes (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordNameComponent)
};
