#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    refreshData();
    mFilteredPresets = mAllPresets;
    PRESET_FOLDER.createDirectory();
}

BrowserState::~BrowserState()
{
}

//==============================================================================
void BrowserState::refreshData()
{
    mTags = mTagsFile.getAllProperties();
    mTagNames = mTags.getAllKeys();
    mFavPathNames = StringArray::fromTokens (mFavoritesFile.getValue ("favorites"), ";", "");

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
StringArray BrowserState::getTagNames()
{
    return mTagNames;
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
void BrowserState::handleClickCreateTag()
{
    if (!System::isValidFileName (mNewTagText) || mTagsFile.containsKey (mNewTagText)) { return; }

    mTagsFile.setValue (mNewTagText, "");

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTagCreated;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleClickDelete (const int inIndexValue)
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

void BrowserState::handleClickFavorite (const int inIndexValue)
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
void BrowserState::handleNewTagTextChanged (String inNewTagText)
{
    mNewTagText = inNewTagText;
}

void BrowserState::handlePresetFilterTextChanged (String inPresetFilterText)
{
    mPresetFilterText = inPresetFilterText;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetFilterTextChanged;
    message->messageVar1 = mPresetFilterText;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleClickLeftArrow (String inPresetName)
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

void BrowserState::handleClickRightArrow (String inPresetName)
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
