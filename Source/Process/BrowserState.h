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

    //==============================================================================
    bool getIsFavoritesOn();
    void toggleFavorites();

    //==============================================================================
    void handleMouseClickOnDelete (const int indexValue);
    void handleMouseClickOnFavorite (const int indexValue);

private:
    //==============================================================================
    juce::Array<juce::Array<String>> mPresetNames;

    bool mIsFavoritesOn = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
