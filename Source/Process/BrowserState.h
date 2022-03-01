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
    void refreshData();
    void filterPresets();

    //==============================================================================
    Array<File> getAllPresetFiles();
    juce::Array<Preset> getFilteredPresets();

    //==============================================================================
    StringArray getTagNames();

    //==============================================================================
    bool isFavorite (String presetName);
    int getUnfilteredIndex (String presetName);

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
    void handleClickCreateTag();
    void handleClickDeleteTag (const String name);

    //==============================================================================
    void handleClickFavorite (const int indexValue);
    void handleClickDeletePreset (const int indexValue);

    //==============================================================================
    void handleNewTagTextChanged (String newTagText);
    void handlePresetFilterTextChanged (String filterText);

    //==============================================================================
    void handleClickLeftArrow (String presetName);
    void handleClickRightArrow (String presetName);

private:
    //==============================================================================
    Array<File> mAllPresetFiles;
    juce::Array<Preset> mAllPresets;
    juce::Array<Preset> mFilteredPresets;

    StringPairArray mTags;
    StringArray mTagNames;
    StringArray mFavPathNames;

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
