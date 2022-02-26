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
void BrowserState::toggleFavorites()
{
    mIsFavoritesOn = !mIsFavoritesOn;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleFavorites;
    sendMessage (message, ListenerType::kSync);
}

bool BrowserState::isFavoritesOn()
{
    return mIsFavoritesOn;
}

//==============================================================================
void BrowserState::toggleTagManager()
{
    mIsTagManagerVisible = !mIsTagManagerVisible;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleTagManager;
    sendMessage (message, ListenerType::kSync);
}

bool BrowserState::isTagManagerVisible()
{
    return mIsTagManagerVisible;
}

//==============================================================================
void BrowserState::toggleTagSelector()
{
    mIsTagSelectorOn = !mIsTagSelectorOn;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleTagSelector;
    sendMessage (message, ListenerType::kSync);
}

bool BrowserState::isTagSelectorOn()
{
    return mIsTagSelectorOn;
}

//==============================================================================
void BrowserState::filterPresets()
{
    mFilteredPresets.clear();

    if (!mIsFavoritesOn && mPresetFilterText.isEmpty())
    {
        mFilteredPresets = mAllPresets;
    }

    if (mIsFavoritesOn && mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite)
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    if (!mIsFavoritesOn && !mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.fileName.containsIgnoreCase (mPresetFilterText))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    if (mIsFavoritesOn && !mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite && preset.fileName.containsIgnoreCase (mPresetFilterText))
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
void BrowserState::handlePresetFilterTextChanged (String inPresetFilterText)
{
    mPresetFilterText = inPresetFilterText;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFilterTextChanged;
    message->messageVar1 = mPresetFilterText;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleNewTagTextChanged (String inNewTagText)
{
    mNewTagText = inNewTagText;
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
