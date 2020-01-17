#include "BrowserState.h"

//==============================================================================
BrowserState::BrowserState()
{
    for (int index = 1; index <= 30; index++)
    {
        String presetName = "Preset " + std::to_string(index);
        mPresetNames[presetName] = false;
    }
}

BrowserState::~BrowserState()
{
}

//==============================================================================
std::map<String, bool, std::less<String>> BrowserState::getPresetNames()
{
    return mPresetNames;
}
