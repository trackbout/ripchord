#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Images.h"

//==============================================================================
class PresetArrowsComponent : public Component
{
public:
    //==============================================================================
    PresetArrowsComponent();
    ~PresetArrowsComponent();

    void resized() override;

private:
    //==============================================================================
    Images mImages;

    DrawableButton mLeftArrowButton { "", DrawableButton::ImageStretched };
    DrawableButton mRightArrowButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetArrowsComponent)
};
