#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "TextLabel.h"
#include "Images.h"

//==============================================================================
class PresetArrowsComponent : public Component
{
public:
    //==============================================================================
    PresetArrowsComponent();
    ~PresetArrowsComponent();

    void resized() override;
    void updateTextLabel (String presetName);

    //==============================================================================
    std::function<void()> onLeftArrowClick;
    std::function<void()> onRightArrowClick;

private:
    //==============================================================================
    Images mImages;
    TextLabel mPresetNameLabel { "", "init" };
    DrawableButton mLeftArrowButton { "", DrawableButton::ImageStretched };
    DrawableButton mRightArrowButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetArrowsComponent)
};
