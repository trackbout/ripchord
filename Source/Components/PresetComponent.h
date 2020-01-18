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
    PresetComponent (const String fileName, const int indexValue);
    ~PresetComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;

    //==============================================================================
    std::function<void (const int indexValue)> onDelete;

private:
    //==============================================================================
    Images mImages;
    Label mPresetLabel;
    const int mIndexValue;

    PresetDeleteComponent mPresetDelete;

    DrawableButton mStarButton { "", DrawableButton::ImageStretched };
    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    void handleDelete();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetComponent)
};
