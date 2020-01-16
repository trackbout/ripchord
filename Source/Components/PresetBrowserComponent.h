#pragma once

#include "JuceHeader.h"
#include "PresetComponent.h"

//==============================================================================
class PresetBrowserComponent : public Component
{
public:
    //==============================================================================
    PresetBrowserComponent();
    ~PresetBrowserComponent();

    //==============================================================================
    void resized() override;
    void setViewedSize (int width, int height);

private:
    //==============================================================================
    OwnedArray<PresetComponent> mPresetComponents;

    int mPresetHeight = 0;
    int mPresetWidth = 0;
    int mSpaceHeight = 0;
    int mSpaceWidth = 0;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetBrowserComponent)
};
