#pragma once

#include "JuceHeader.h"
#include "Presets.h"
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
    juce::Array<Preset> getPresets();

    //==============================================================================
    String getFilterText();
    bool getIsFavoritesOn();
    void toggleFavorites();

    //==============================================================================
    void handleMouseClickOnDelete (const int indexValue);
    void handleMouseClickOnFavorite (const int indexValue);
    void handlePresetFilterTextChanged (String filterText);

private:
    //==============================================================================
    juce::Array<Preset> mPresets;

    String mFilterText = "";
    bool mIsFavoritesOn = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
