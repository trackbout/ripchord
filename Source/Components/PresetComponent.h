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
    PresetComponent (const int indexValue, const String fileName, const bool isFavorite);
    ~PresetComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;

    //==============================================================================
    std::function<void (const int indexValue)> onDelete;
    std::function<void (const int indexValue)> onFavorite;

private:
    //==============================================================================
    Images mImages;
    Label mPresetLabel;
    const int mIndexValue;
    const bool mIsFavorite;

    PresetDeleteComponent mPresetDelete;

    DrawableButton mStarButton { "", DrawableButton::ImageStretched };
    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetComponent)
};
