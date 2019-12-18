#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Images.h"
#include "PresetDeleteComponent.h"

//==============================================================================
class PresetComponent : public Component
{
public:
    //==============================================================================
    PresetComponent();
    ~PresetComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;

private:
    //==============================================================================
    Images mImages;

    File mPresetFile;
    Label mPresetLabel { "", "preset" };

    PresetDeleteComponent mPresetDeleteComponent;

    DrawableButton mStarButton { "", DrawableButton::ImageStretched };
    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetComponent)
};
