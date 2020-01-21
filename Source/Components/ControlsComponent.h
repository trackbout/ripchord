#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class ControlsComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    ControlsComponent (MainProcess&);
    ~ControlsComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
