#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class BrowserState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    BrowserState();
    ~BrowserState();

    //==============================================================================
    juce::Array<juce::Array<String>> getPresetNames();

private:
    //==============================================================================
    juce::Array<juce::Array<String>> mPresetNames;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
