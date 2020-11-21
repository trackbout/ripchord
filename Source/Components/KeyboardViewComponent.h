#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"
#include "OutputKeyboardComponent.h"
#include "InputKeyboardComponent.h"
#include "PlayControlsComponent.h"
#include "EditControlsComponent.h"
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
    bool keyPressed (const KeyPress& key) override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    ControlsState& mControlsState;
    MidiState& mMidiState;

    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    Images mImages;
    DrawableButton mPowerButton { "", DrawableButton::ImageStretched };
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };
    DrawableButton mPresetsButton { "", DrawableButton::ImageStretched };

    OutputKeyboardComponent mOutputKeyboard;
    InputKeyboardComponent mInputKeyboard;
    PlayControlsComponent mPlayControls;
    EditControlsComponent mEditControls;
    PresetNameComponent mPresetName;
    ChordNameComponent mChordName;

    void handleTogglePower (const DataMessage* message);
    void handleToggleMode (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
