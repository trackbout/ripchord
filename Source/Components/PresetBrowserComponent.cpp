#include "JuceHeader.h"
#include "PresetBrowserComponent.h"

//==============================================================================
PresetBrowserComponent::PresetBrowserComponent()
{
}

PresetBrowserComponent::~PresetBrowserComponent()
{
}

//==============================================================================
void PresetBrowserComponent::resized()
{
    for (int i = 0; i < mPresetComponents.size(); ++i)
    {
        int x = (i % PRESETS_PER_ROW) * (mPresetWidth + mSpaceWidth) + mSpaceWidth;
        int y = (i / PRESETS_PER_ROW) * (mPresetHeight + mSpaceHeight) + mSpaceHeight;
        mPresetComponents[i]->setBounds (x, y, mPresetWidth, mPresetHeight);
    }
}

void PresetBrowserComponent::setViewedSize (int inWidth, int inHeight)
{
    mPresetWidth = int (inWidth * (PRESET_WIDTH / PRESET_LIST_WIDTH));
    mSpaceWidth = (inWidth - (PRESETS_PER_ROW * mPresetWidth)) / (PRESETS_PER_ROW + 1);

    mPresetHeight = int (inHeight * (ITEM_HEIGHT / PRESET_LIST_HEIGHT));
    mSpaceHeight = mPresetHeight * (HALF_SPACE / ITEM_HEIGHT);
}
