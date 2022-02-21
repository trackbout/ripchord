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
    enum TagManager { HiddenTm, VisibleTm };
    enum PresetTagger { HiddenPt, VisiblePt };

    //==============================================================================
    void toggleTagManager();
    bool isTagManagerHidden();
    bool isTagManagerVisible();

    //==============================================================================
    void togglePresetTagger();
    bool isPresetTaggerHidden();
    bool isPresetTaggerVisible();

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
    void handleMouseDownOnFavorites();
    void handlePresetFilterTextChanged (String filterText);

private:
    //==============================================================================
    TagManager mTagManager = TagManager::HiddenTm;
    PresetTagger mPresetTagger = PresetTagger::HiddenPt;

    Array<File> mAllPresetFiles;
    juce::Array<Preset> mAllPresets;
    juce::Array<Preset> mFilteredPresets;

    String mFilterText = "";
    bool mIsFavoritesOn = false;
    int getFilteredIndex (String presetName);

    PropertiesFile mFavoritesFile { System::createPluginPropertiesOptions ("favorites") };
    StringArray mFavPathNames { StringArray::fromTokens (mFavoritesFile.getValue ("favorites"), ";", "") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
