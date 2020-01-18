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
