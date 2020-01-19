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
    juce::Array<juce::Array<var>> getPresets();

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
    // [0]: indexValue, [1]: fileName, [2]: isFavorite
    juce::Array<juce::Array<var>> mPresets;

    String mFilterText = "";
    bool mIsFavoritesOn = false;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
