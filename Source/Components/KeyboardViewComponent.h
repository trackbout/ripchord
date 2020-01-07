#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "Images.h"
#include "TextInput.h"
#include "MainProcess.h"
#include "DataMessage.h"
#include "DataMessageListener.h"
#include "OutputKeyboardComponent.h"
#include "InputKeyboardComponent.h"
#include "PresetNameComponent.h"

//==============================================================================
class KeyboardViewComponent : public Component, public DataMessageListener
{
public:
    //=============================================================================
    KeyboardViewComponent (MainProcess&);
    ~KeyboardViewComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;
    void handleModeUpdated (const DataMessage* message);
    void handleEditModeInputNote (const DataMessage* message);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    OutputKeyboardComponent mOutputKeyboard;
    InputKeyboardComponent mInputKeyboard;
    PresetNameComponent mPresetName;

    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    Images mImages;
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };
    DrawableButton mPresetsButton { "", DrawableButton::ImageStretched };

    Label mChordNameLabel;
    TextInput mChordNameInput;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
