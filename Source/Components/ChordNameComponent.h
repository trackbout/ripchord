#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class ChordNameComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    ChordNameComponent (MainProcess&);
    ~ChordNameComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordNameComponent)
};
