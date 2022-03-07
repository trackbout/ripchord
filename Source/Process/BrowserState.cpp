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
    mAllPresets.clear();
    mAllPresetFiles.clear();
    mAllPresetFiles = Presets::getSortedPresetFiles();
    mFavPathNames = StringArray::fromTokens (mFavoritesFile.getValue ("favorites"), ";", "");

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

    // ALL PRESETS
    if (!mIsFavoritesOn && mSelectedTags.isEmpty() && mPresetFilterText.isEmpty())
    {
        mFilteredPresets = mAllPresets;
    }

    // ONLY FAVS
    if (mIsFavoritesOn && mSelectedTags.isEmpty() && mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite)
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    // ONLY TAGS
    if (!mIsFavoritesOn && !mSelectedTags.isEmpty() && mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (isInSelectedTags (preset.indexValue))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    // ONLY SEARCH
    if (!mIsFavoritesOn && mSelectedTags.isEmpty() && !mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.fileName.containsIgnoreCase (mPresetFilterText))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    // FAVS + TAGS
    if (mIsFavoritesOn && !mSelectedTags.isEmpty() && mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite && isInSelectedTags (preset.indexValue))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    // FAVS + SEARCH
    if (mIsFavoritesOn && mSelectedTags.isEmpty() && !mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite && preset.fileName.containsIgnoreCase (mPresetFilterText))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    // TAGS + SEARCH
    if (!mIsFavoritesOn && !mSelectedTags.isEmpty() && !mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (isInSelectedTags (preset.indexValue) && preset.fileName.containsIgnoreCase (mPresetFilterText))
            {
                mFilteredPresets.add (preset);
            }
        }
    }

    // FAVS + TAGS + SEARCH
    if (mIsFavoritesOn && !mSelectedTags.isEmpty() && !mPresetFilterText.isEmpty())
    {
        for (Preset& preset : mAllPresets)
        {
            if (preset.isFavorite && isInSelectedTags (preset.indexValue) && preset.fileName.containsIgnoreCase (mPresetFilterText))
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
StringArray BrowserState::getAllTagNames()
{
    StringPairArray allTags = mTagsFile.getAllProperties();
    StringArray allTagNames = allTags.getAllKeys();
    return allTagNames;
}

bool BrowserState::isTagSelected (const String inTagName)
{
    if (isTagSelectorOn()) { return false; }
    return mSelectedTags.contains (inTagName);
}

bool BrowserState::isTagAssignable (const String inTagName)
{
    if (!isTagSelectorOn()) { return false; }
    return mAssignableTag == inTagName;
}

//==============================================================================
bool BrowserState::isInSelectedTags (const int inIndexValue)
{
    int matches = 0;
    File file = mAllPresetFiles[inIndexValue];
    if (!file.existsAsFile() || mSelectedTags.size() == 0) { return false; }

    for (int index = 0; index < mSelectedTags.size(); index++)
    {
        const String tagName = mSelectedTags[index];
        StringArray taggedFileNames = StringArray::fromTokens (mTagsFile.getValue (tagName), ";", "");
        if (taggedFileNames.contains(file.getFileNameWithoutExtension())) { matches += 1; }
    }

    return matches > 0;
}

bool BrowserState::isInAssignableTag (const String inPresetName)
{
    int indexValue = getUnfilteredIndex (inPresetName);
    File file = mAllPresetFiles[indexValue];
    if (!file.existsAsFile() || mAssignableTag.isEmpty()) { return false; }

    StringArray taggedFileNames = StringArray::fromTokens (mTagsFile.getValue (mAssignableTag), ";", "");
    return taggedFileNames.contains(file.getFileNameWithoutExtension());
}

//==============================================================================
bool BrowserState::isFavorite (const String inPresetName)
{
    int indexValue = getUnfilteredIndex (inPresetName);
    return mAllPresets[indexValue].isFavorite;
}

int BrowserState::getUnfilteredIndex (const String inPresetName)
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
    mSelectedTags.clear();
    mAssignableTag.clear();
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
    mTagsFile.saveIfNeeded();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTagCreated;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleClickDeleteTag (const String inName)
{
    mTagsFile.removeValue (inName);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTagDeleted;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void BrowserState::handleClickAssignableTag (const String inName)
{
    if (mAssignableTag == inName)
    {
        mAssignableTag.clear();
    }
    else
    {
        mAssignableTag = inName;
    }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kClickAssignableTag;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleClickSelectableTag (const String inName)
{
    if (mSelectedTags.contains (inName))
    {
        mSelectedTags.removeString (inName);
    }
    else
    {
        mSelectedTags.addIfNotAlreadyThere (inName);
    }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kClickSelectableTag;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
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

void BrowserState::handleClickDeletePreset (const int inIndexValue)
{
    File file = mAllPresetFiles[inIndexValue];
    if (!file.existsAsFile()) { return; }

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

void BrowserState::handleClickPresetTagger (const int inIndexValue)
{
    File file = mAllPresetFiles[inIndexValue];
    if (!file.existsAsFile() || mAssignableTag.isEmpty()) { return; }

    StringArray taggedPathNames = StringArray::fromTokens (mTagsFile.getValue (mAssignableTag), ";", "");

    if (taggedPathNames.contains (file.getFileNameWithoutExtension()))
    {
        taggedPathNames.removeString (file.getFileNameWithoutExtension());
    }
    else
    {
        taggedPathNames.addIfNotAlreadyThere (file.getFileNameWithoutExtension());
    }

    mTagsFile.setValue (mAssignableTag, taggedPathNames.joinIntoString (";"));
    mTagsFile.saveIfNeeded();

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kClickPresetTagger;
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
