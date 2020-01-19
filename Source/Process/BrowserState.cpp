#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    refreshPresets();
}

BrowserState::~BrowserState()
{
}

//==============================================================================
void BrowserState::refreshPresets()
{
    mPresets.clear();
    Array<File> files = Presets::getSortedPresetFiles();

    for (int index = 0; index < files.size(); index++)
    {
        Preset preset;
        preset.indexValue = index;
        preset.fileName = files[index].getFileNameWithoutExtension();
        preset.isFavorite = mFavoritesFiles.contains (files[index].getFullPathName());
        mPresets.add (preset);
    }
}

juce::Array<Preset> BrowserState::getPresets()
{
    return mPresets;
}

//==============================================================================
String BrowserState::getFilterText()
{
    return mFilterText;
}

bool BrowserState::getIsFavoritesOn()
{
    return mIsFavoritesOn;
}

void BrowserState::toggleFavorites()
{
    mIsFavoritesOn = !mIsFavoritesOn;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleFavorites;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleMouseClickOnDelete (const int inIndexValue)
{
    // 1. Update ripchord.favorites
    // 2. Delete file based on file name
    // 3. Remove indexValue from presets
    mPresets.remove (inIndexValue);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetsChanged;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleMouseClickOnFavorite (const int inIndexValue)
{
    Preset preset = mPresets[inIndexValue];
    File file = Presets::getSortedPresetFiles()[inIndexValue];

    if (preset.isFavorite)
    {
        preset.isFavorite = false;
        mFavoritesFiles.removeString (file.getFullPathName());
    }
    else
    {
        preset.isFavorite = true;
        mFavoritesFiles.addIfNotAlreadyThere (file.getFullPathName());
    }

    mPresets.set (inIndexValue, preset);
    mPropertiesFile.setValue ("favorites", mFavoritesFiles.joinIntoString (";"));
    mPropertiesFile.saveIfNeeded();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetsChanged;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handlePresetFilterTextChanged (String inFilterText)
{
    mFilterText = inFilterText;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFilterTextChanged;
    sendMessage (message, ListenerType::kSync);
}
