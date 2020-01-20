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
    mAllPresets.clear();
    mAllPresetFiles.clear();
    mAllPresetFiles = Presets::getSortedPresetFiles();

    for (int index = 0; index < mAllPresetFiles.size(); index++)
    {
        Preset preset;
        preset.indexValue = index;
        preset.fileName = mAllPresetFiles[index].getFileNameWithoutExtension();
        preset.isFavorite = mFavPathNames.contains (mAllPresetFiles[index].getFullPathName());
        mAllPresets.add (preset);
    }
}

Array<File> BrowserState::getAllPresetFiles()
{
    return mAllPresetFiles;
}

juce::Array<Preset> BrowserState::getAllPresets()
{
    return mAllPresets;
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

//==============================================================================
void BrowserState::handleMouseClickOnDelete (const int inIndexValue)
{
    File file = mAllPresetFiles[inIndexValue];

    if (mFavPathNames.contains (file.getFullPathName()))
    {
        mFavPathNames.removeString (file.getFullPathName());
        mPropertiesFile.setValue ("favorites", mFavPathNames.joinIntoString (";"));
        mPropertiesFile.saveIfNeeded();
    }

    mAllPresets.remove (inIndexValue);
    file.deleteFile();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileDeleted;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleMouseClickOnFavorite (const int inIndexValue)
{
    Preset preset = mAllPresets[inIndexValue];
    File file = mAllPresetFiles[inIndexValue];

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

    mAllPresets.set (inIndexValue, preset);
    mPropertiesFile.setValue ("favorites", mFavPathNames.joinIntoString (";"));
    mPropertiesFile.saveIfNeeded();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileFavorited;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleMouseClickOnLeftArrow()
{
    DBG ("LEFT");
}

void BrowserState::handleMouseClickOnRightArrow()
{
    DBG ("RIGHT");
}

//==============================================================================
void BrowserState::handleMouseClickOnFavorites()
{
    mIsFavoritesOn = !mIsFavoritesOn;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleFavorites;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handlePresetFilterTextChanged (String inFilterText)
{
    mFilterText = inFilterText;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFilterTextChanged;
    sendMessage (message, ListenerType::kSync);
}
