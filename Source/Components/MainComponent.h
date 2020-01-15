#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessage.h"
#include "DataMessageListener.h"
#include "KeyboardViewComponent.h"
#include "PresetViewComponent.h"
#include "MenuComponent.h"

//==============================================================================
class MainComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    MainComponent (MainProcess&);
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    KeyboardViewComponent mKeyboardViewComponent;
    PresetViewComponent mPresetViewComponent;
    MenuComponent mMenuComponent;

    Images mImages;
    Label mTitleLabel { "", "ripchord" };
    DrawableButton mMenuButton { "", DrawableButton::ImageStretched };

    void handleViewUpdated (const DataMessage* message);
    void handleMenuUpdated (const DataMessage* message);
    void handlePresetFileNew (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
