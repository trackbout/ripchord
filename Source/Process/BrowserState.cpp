#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    for (int index = 1; index <= 30; index++)
    {
        juce::Array<String> presetName;
        presetName.add ("Preset " + std::to_string (index));
        presetName.add ("false");
        mPresetNames.add (presetName);
    }
}

BrowserState::~BrowserState()
{
}

//==============================================================================
juce::Array<juce::Array<String>> BrowserState::getPresetNames()
{
    return mPresetNames;
}

//==============================================================================
void BrowserState::handleMouseClickOnDelete (const int inIndexValue)
{
    // 1. Update ripchord.favorites
    // 2. Delete file based on file name
    // 3. Remove indexValue from presetNames
    mPresetNames.remove (inIndexValue);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetNamesUpdated;
    sendMessage (message, ListenerType::kSync);
}

void BrowserState::handleMouseClickOnFavorite (const int inIndexValue)
{
    // 1. Update ripchord.favorites
    // 2. Update indexValue in presetNames
    juce::Array<String> nextPresetName = mPresetNames[inIndexValue];
    nextPresetName.set (1, nextPresetName[1] == "false" ? "true" : "false");
    mPresetNames.set (inIndexValue, nextPresetName);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kPresetNamesUpdated;
    sendMessage (message, ListenerType::kSync);
}
