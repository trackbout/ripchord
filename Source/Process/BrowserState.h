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
    StringArray getAllTagNames();
    bool isTagSelected (const String tagName);
    bool isTagAssignable (const String tagName);

    //==============================================================================
    bool isInSelectedTags (const int indexValue);
    bool isInAssignableTag (const String presetName);

    //==============================================================================
    bool isFavorite (const String presetName);
    int getUnfilteredPresetIndex (const String presetName);

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
    void handleClickDeleteTag (const String tagName);
    void handleClickShiftTag (const String tagName, const String direction);

    //==============================================================================
    void handleClickAssignableTag (const String tagName);
    void handleClickSelectableTag (const String tagName);

    //==============================================================================
    void handleClickFavorite (const int indexValue);
    void handleClickDeletePreset (const int indexValue);
    void handleClickPresetTagger (const int indexValue);

    //==============================================================================
    void handleNewTagTextChanged (const String newTagText);
    void handlePresetFilterTextChanged (const String filterText);

    //==============================================================================
    void handleClickLeftArrow (const String presetName);
    void handleClickRightArrow (const String presetName);

private:
    //==============================================================================
    Array<File> mAllPresetFiles;
    juce::Array<Preset> mAllPresets;
    juce::Array<Preset> mFilteredPresets;

    String mAssignableTag;
    StringArray mSelectedTags;
    StringArray mFavPresetNames;

    String mNewTagText = "";
    String mPresetFilterText = "";

    bool mIsFavoritesOn = false;
    bool mIsTagSelectorOn = false;
    bool mIsTagManagerVisible = false;

    void scrubFavs();
    void scrubTags();
    int getFilteredPresetIndex (const String presetName);

    PropertiesFile mTagsFile { System::createPluginPropertiesOptions ("tags") };
    PropertiesFile mFavoritesFile { System::createPluginPropertiesOptions ("favorites") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
