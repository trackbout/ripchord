#pragma once

#include "JuceHeader.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "Interface.h"
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
    void handleModeUpdated (const DataMessage* message);
    void handleEditModeInputNote (const DataMessage* message);
    void handleEditModeOutputNotes (const DataMessage* message);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    TextLabel mChordNameLabel;
    TextInput mChordNameInput;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordNameComponent)
};
