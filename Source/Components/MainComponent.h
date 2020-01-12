#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Constants.h"
#include "Interface.h"
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

    KeyboardViewComponent mKeyboardViewComponent;
    PresetViewComponent mPresetViewComponent;
    MenuComponent mMenuComponent;

    Images mImages;
    Label mTitleLabel { "", "ripchord" };
    DrawableButton mMenuButton { "", DrawableButton::ImageStretched };

    void handleViewUpdated();
    void handleMenuUpdated();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
