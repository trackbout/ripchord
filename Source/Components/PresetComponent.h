#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
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

    //==============================================================================
    void setFileName (String fileName);
    void setIsFavorite (bool isFavorite);

private:
    //==============================================================================
    Images mImages;
    Label mPresetLabel;
    bool mIsFavorite;

    PresetDeleteComponent mPresetDeleteComponent;

    DrawableButton mStarButton { "", DrawableButton::ImageStretched };
    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetComponent)
};
