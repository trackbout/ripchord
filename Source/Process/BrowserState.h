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
    Array<File> getPresetFiles();
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
    Array<File> mPresetFiles;
    juce::Array<Preset> mPresets;

    String mFilterText = "";
    bool mIsFavoritesOn = false;

    PropertiesFile mPropertiesFile { System::createPluginPropertiesOptions ("favorites") };
    StringArray mFavPathNames { StringArray::fromTokens (mPropertiesFile.getValue ("favorites"), ";", "") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BrowserState)
};
