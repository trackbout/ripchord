#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Images.h"
#include "MainProcess.h"
#include "DataMessageListener.h"
#include "OutputKeyboardComponent.h"
#include "InputKeyboardComponent.h"
#include "PresetNameComponent.h"
#include "ChordNameComponent.h"

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

    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    Images mImages;
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };
    DrawableButton mPresetsButton { "", DrawableButton::ImageStretched };
    DrawableButton mSaveButton { "", DrawableButton::ImageStretched };

    OutputKeyboardComponent mOutputKeyboard;
    InputKeyboardComponent mInputKeyboard;
    PresetNameComponent mPresetName;
    ChordNameComponent mChordName;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
