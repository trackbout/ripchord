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
    BrowserState& mBrowserState;
    PresetState& mPresetState;
    MidiState& mMidiState;

    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    Images mImages;
    DrawableButton mQuickFav { "", DrawableButton::ImageStretched };
    DrawableButton mMenuButton { "", DrawableButton::ImageStretched };
    DrawableButton mPowerButton { "", DrawableButton::ImageStretched };
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };
    DrawableButton mPresetsButton { "", DrawableButton::ImageStretched };
    DrawableButton mInputKeyboardBg { "", DrawableButton::ImageStretched };
    DrawableButton mOutputKeyboardBg { "", DrawableButton::ImageStretched };

    OutputKeyboardComponent mOutputKeyboard;
    InputKeyboardComponent mInputKeyboard;
    PlayControlsComponent mPlayControls;
    EditControlsComponent mEditControls;
    PresetNameComponent mPresetName;
    ChordNameComponent mChordName;

    bool mSkipKeypress = true;

    void handleToggleMode (const DataMessage* message);
    void handleTogglePower (const DataMessage* message);
    void handleToggleFavorite (const DataMessage* message);
    void handlePresetFileLoaded (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
