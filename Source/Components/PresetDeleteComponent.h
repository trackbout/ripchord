#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"

//==============================================================================
class PresetDeleteComponent : public Component
{
public:
    //==============================================================================
    PresetDeleteComponent (const int indexValue);
    ~PresetDeleteComponent();

    void paint (Graphics& graphics) override;
    void resized() override;

private:
    //==============================================================================
    Images mImages;
    const int mIndexValue;

    DrawableButton mCancelButton { "", DrawableButton::ImageStretched };
    DrawableButton mDeleteButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetDeleteComponent)
};
