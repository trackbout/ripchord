#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "TextLabel.h"
#include "TextInput.h"
#include "Images.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class PresetNameComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    PresetNameComponent (MainProcess&);
    ~PresetNameComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    std::function<void()> onLeftArrowClick;
    std::function<void()> onRightArrowClick;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;
    void handleModeUpdated (const DataMessage* message);
    void handlePresetNameUpdated (const DataMessage* message);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    Images mImages;
    DrawableButton mLeftArrowButton { "", DrawableButton::ImageStretched };
    DrawableButton mRightArrowButton { "", DrawableButton::ImageStretched };

    TextLabel mPresetNameLabel { "", "init" };
    TextInput mPresetNameInput;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetNameComponent)
};