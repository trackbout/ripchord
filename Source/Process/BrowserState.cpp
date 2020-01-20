#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    refreshPresetFiles();
    mFilteredPresets = mAllPresets;
}

BrowserState::~BrowserState()
{
}

//==============================================================================
void BrowserState::filterPresets()
{
    mFilteredPresets.clear();

    if (!mIsFavoritesOn && mFilterText.isEmpty())
    {
        mFilteredPresets = mAllPresets;
    }

    if (mIsFavoritesOn && mFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite)
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    if (!mIsFavoritesOn && !mFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.fileName.containsIgnoreCase (mFilterText))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    if (mIsFavoritesOn && !mFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite && preset.fileName.containsIgnoreCase (mFilterText))
            {
                mFilteredPresets.add (preset);
            }
        }
    }
}

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

juce::Array<Preset> BrowserState::getFilteredPresets()
{
    return mFilteredPresets;
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
    message->messageVar1 = mIsFavoritesOn;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handlePresetFilterTextChanged (String inFilterText)
{
    mFilterText = inFilterText;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFilterTextChanged;
    message->messageVar1 = mFilterText;
    sendMessage (message, ListenerType::kSync);
}
