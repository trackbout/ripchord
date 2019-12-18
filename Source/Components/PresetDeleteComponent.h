#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Images.h"

//==============================================================================
class PresetDeleteComponent : public Component
{
public:
    //==============================================================================
    PresetDeleteComponent();
    ~PresetDeleteComponent();

    void paint (Graphics& graphics) override;
    void resized() override;

private:
    //==============================================================================
    Images mImages;
    DrawableButton mCancelButton { "", DrawableButton::ImageStretched };
    DrawableButton mDeleteButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetDeleteComponent)
};