#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"
#include "OutputKeyboardComponent.h"
#include "InputKeyboardComponent.h"
#include "PresetNameComponent.h"
#include "ChordNameComponent.h"
#include "ControlsComponent.h"

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
    bool keyPressed (const KeyPress& key) override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;
    MidiState& mMidiState;

    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    Images mImages;
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };
    DrawableButton mPresetsButton { "", DrawableButton::ImageStretched };
    DrawableButton mEditRightButton { "", DrawableButton::ImageStretched };
    DrawableButton mEditLeftButton { "", DrawableButton::ImageStretched };
    DrawableButton mSaveButton { "", DrawableButton::ImageStretched };
    DrawableButton mSuccess { "", DrawableButton::ImageStretched };

    OutputKeyboardComponent mOutputKeyboard;
    InputKeyboardComponent mInputKeyboard;
    PresetNameComponent mPresetName;
    ChordNameComponent mChordName;
    ControlsComponent mControls;

    void handleToggleMode (const DataMessage* message);
    void handlePresetFileNew (const DataMessage* message);
    void handlePresetFileSaved (const DataMessage* message);
    void handlePresetFileLoaded (const DataMessage* message);
    void handlePresetModified (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
