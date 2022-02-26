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
    void toggleFavorites();
    bool isFavoritesOn();

    //==============================================================================
    void toggleTagManager();
    bool isTagManagerVisible();

    //==============================================================================
    void toggleTagSelector();
    bool isTagSelectorOn();

    //==============================================================================
    void filterPresets();
    void refreshPresetFiles();

    //==============================================================================
    Array<File> getAllPresetFiles();
    juce::Array<Preset> getFilteredPresets();

    //==============================================================================
    bool isFavorite (String presetName);
    int getUnfilteredIndex (String presetName);

    //==============================================================================
    void handleMouseDownOnDelete (const int indexValue);
    void handleMouseDownOnFavorite (const int indexValue);

    //==============================================================================
    void handleMouseDownOnLeftArrow (String presetName);
    void handleMouseDownOnRightArrow (String presetName);

    //==============================================================================
    void handlePresetFilterTextChanged (String filterText);
    void handleNewTagTextChanged (String newTagText);

private:
    //==============================================================================
    bool mIsFavoritesOn = false;
    bool mIsTagSelectorOn = false;
    bool mIsTagManagerVisible = false;

    String mNewTagText = "";
    String mPresetFilterText = "";

    Array<File> mAllPresetFiles;
    juce::Array<Preset> mAllPresets;
    juce::Array<Preset> mFilteredPresets;

    int getFilteredIndex (String presetName);

    PropertiesFile mFavoritesFile { System::createPluginPropertiesOptions ("favorites") };
    StringArray mFavPathNames { StringArray::fromTokens (mFavoritesFile.getValue ("favorites"), ";", "") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
