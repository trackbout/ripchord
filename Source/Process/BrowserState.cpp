#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    refreshPresetFiles();
}

BrowserState::~BrowserState()
{
}

//==============================================================================
void BrowserState::refreshPresetFiles()
{
    mPresets.clear();
    mPresetFiles.clear();
    mPresetFiles = Presets::getSortedPresetFiles();

    for (int index = 0; index < mPresetFiles.size(); index++)
    {
        Preset preset;
        preset.indexValue = index;
        preset.fileName = mPresetFiles[index].getFileNameWithoutExtension();
        preset.isFavorite = mFavPathNames.contains (mPresetFiles[index].getFullPathName());
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
    File file = mPresetFiles[inIndexValue];

    if (mFavPathNames.contains (file.getFullPathName()))
    {
        mFavPathNames.removeString (file.getFullPathName());
        mPropertiesFile.setValue ("favorites", mFavPathNames.joinIntoString (";"));
        mPropertiesFile.saveIfNeeded();
    }

    mPresets.remove (inIndexValue);
    file.deleteFile();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetsChanged;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleMouseClickOnFavorite (const int inIndexValue)
{
    Preset preset = mPresets[inIndexValue];
    File file = mPresetFiles[inIndexValue];

    if (preset.isFavorite)
    {
        preset.isFavorite = false;
        mFavPathNames.removeString (file.getFullPathName());
    }
    else
    {
        preset.isFavorite = true;
        mFavPathNames.addIfNotAlreadyThere (file.getFullPathName());
    }

    mPresets.set (inIndexValue, preset);
    mPropertiesFile.setValue ("favorites", mFavPathNames.joinIntoString (";"));
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
