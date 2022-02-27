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
    void refreshPresetFiles();
    void filterPresets();

    //==============================================================================
    Array<File> getAllPresetFiles();
    juce::Array<Preset> getFilteredPresets();

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
    bool isFavorite (String presetName);
    int getUnfilteredIndex (String presetName);

    //==============================================================================
    void handleMouseDownOnDelete (const int indexValue);
    void handleMouseDownOnFavorite (const int indexValue);

    //==============================================================================
    void handleMouseDownOnLeftArrow (String presetName);
    void handleMouseDownOnRightArrow (String presetName);

    //==============================================================================
    void handleNewTagTextChanged (String newTagText);
    void handlePresetFilterTextChanged (String filterText);

    //==============================================================================
    void handleMouseDownOnCreateTag();

private:
    //==============================================================================
    Array<File> mAllPresetFiles;
    StringArray mFavPathNames;

    juce::Array<Preset> mAllPresets;
    juce::Array<Preset> mFilteredPresets;

    String mNewTagText = "";
    String mPresetFilterText = "";

    bool mIsFavoritesOn = false;
    bool mIsTagSelectorOn = false;
    bool mIsTagManagerVisible = false;

    int getFilteredIndex (String presetName);

    PropertiesFile mTagsFile { System::createPluginPropertiesOptions ("tags") };
    PropertiesFile mFavoritesFile { System::createPluginPropertiesOptions ("favorites") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
