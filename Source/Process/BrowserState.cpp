#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    for (int index = 0; index <= 30; index++)
    {
        String fileName = "Preset " + std::to_string (index);

        juce::Array<var> preset;
        preset.add (index);
        preset.add (fileName);
        preset.add (false);
        mPresets.add (preset);
    }
}

BrowserState::~BrowserState()
{
}

//==============================================================================
juce::Array<juce::Array<var>> BrowserState::getPresets()
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
    // 1. Update ripchord.favorites
    // 2. Update indexValue in presets
    juce::Array<var> nextPreset = mPresets[inIndexValue];
    nextPreset.set (2, !nextPreset[2]);
    mPresets.set (inIndexValue, nextPreset);

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
