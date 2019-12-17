#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "Images.h"
#include "DataMessage.h"
#include "MainProcess.h"
#include "KeyboardComponent.h"
#include "DataMessageListener.h"

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
    void messageReceived (const DataMessage* inMessage) override;
    void handleModeUpdated();

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    KeyboardComponent mOutputKeyboard;
    KeyboardComponent mInputKeyboard;

    Images mImages;
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };
    DrawableButton mPresetsButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
