#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    refreshPresetFiles();
    mFilteredPresets = mAllPresets;
    PRESET_FOLDER.createDirectory();
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

//==============================================================================
Array<File> BrowserState::getAllPresetFiles()
{
    return mAllPresetFiles;
}

juce::Array<Preset> BrowserState::getFilteredPresets()
{
    return mFilteredPresets;
}

//==============================================================================
bool BrowserState::isFavorite (String inPresetName)
{
    int indexValue = getUnfilteredIndex (inPresetName);
    return mAllPresets[indexValue].isFavorite;
}

int BrowserState::getUnfilteredIndex (String inPresetName)
{
    int unfilteredIndex = -1;

    for (int index = 0; index < mAllPresets.size(); index++)
    {
        String presetName = mAllPresets[index].fileName;
        if (presetName == inPresetName) { unfilteredIndex = index; }
    }

    return unfilteredIndex;
}

//==============================================================================
void BrowserState::handleMouseDownOnDelete (const int inIndexValue)
{
    File file = mAllPresetFiles[inIndexValue];

    if (mFavPathNames.contains (file.getFullPathName()))
    {
        mFavPathNames.removeString (file.getFullPathName());
        mFavoritesFile.setValue ("favorites", mFavPathNames.joinIntoString (";"));
        mFavoritesFile.saveIfNeeded();
    }

    mAllPresets.remove (inIndexValue);
    file.deleteFile();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileDeleted;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleMouseDownOnFavorite (const int inIndexValue)
{
    Preset preset = mAllPresets[inIndexValue];
    File file = mAllPresetFiles[inIndexValue];
    if (!file.existsAsFile()) { return; }

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
    mFavoritesFile.setValue ("favorites", mFavPathNames.joinIntoString (";"));
    mFavoritesFile.saveIfNeeded();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFileFavorited;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleMouseDownOnLeftArrow (String inPresetName)
{
    int index = getFilteredIndex (inPresetName);

    if (index > 0) { index = index - 1; }
    else if (index == 0) { index = mFilteredPresets.size() - 1; }
    else if (index == -1 && !mFilteredPresets.isEmpty()) { index = mFilteredPresets.size() - 1; }

    int nextIndex = index >= 0 ? mFilteredPresets[index].indexValue : -1;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentIndexChanged;
    message->messageVar1 = nextIndex;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleMouseDownOnRightArrow (String inPresetName)
{
    int index = getFilteredIndex (inPresetName);

    if (index >= 0 && index < (mFilteredPresets.size() - 1)) { index = index + 1; }
    else if (index == (mFilteredPresets.size() - 1)) { index = 0; }
    else if (index == -1 && !mFilteredPresets.isEmpty()) { index = 0; }

    int nextIndex = index >= 0 ? mFilteredPresets[index].indexValue : -1;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentIndexChanged;
    message->messageVar1 = nextIndex;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleMouseDownOnFavorites()
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

//==============================================================================
int BrowserState::getFilteredIndex (String inPresetName)
{
    int filteredIndex = -1;

    for (int index = 0; index < mFilteredPresets.size(); index++)
    {
        String presetName = mFilteredPresets[index].fileName;
        if (presetName == inPresetName) { filteredIndex = index; }
    }

    return filteredIndex;
}
