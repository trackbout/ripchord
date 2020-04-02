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
    void filterPresets();
    void refreshPresetFiles();

    //==============================================================================
    Array<File> getAllPresetFiles();
    juce::Array<Preset> getFilteredPresets();

    //==============================================================================
    void handleMouseDownOnDelete (const int indexValue);
    void handleMouseDownOnFavorite (const int indexValue);

    //==============================================================================
    void handleMouseDownOnLeftArrow (String presetName);
    void handleMouseDownOnRightArrow (String presetName);

    //==============================================================================
    void handleMouseDownOnFavorites();
    void handlePresetFilterTextChanged (String filterText);

private:
    //==============================================================================
    Array<File> mAllPresetFiles;
    juce::Array<Preset> mAllPresets;
    juce::Array<Preset> mFilteredPresets;

    String mFilterText = "";
    bool mIsFavoritesOn = false;
    int getFilteredIndex (String presetName);

    PropertiesFile mPropertiesFile { System::createPluginPropertiesOptions ("favorites") };
    StringArray mFavPathNames { StringArray::fromTokens (mPropertiesFile.getValue ("favorites"), ";", "") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
