#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "DataMessage.h"
#include "MainProcess.h"
#include "KeyboardViewComponent.h"
#include "PresetViewComponent.h"
#include "DataMessageListener.h"

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
    void messageReceived (const DataMessage* message) override;
    void handleViewUpdated();

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    Label mTitleLabel { "", "ripchord" };
    KeyboardViewComponent mKeyboardViewComponent;
    PresetViewComponent mPresetViewComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
