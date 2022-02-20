#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "Presets.h"
#include "PresetDeleteComponent.h"

//==============================================================================
class PresetComponent : public Component
{
public:
    //==============================================================================
    PresetComponent (Preset preset);
    ~PresetComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;
    void mouseDown (const MouseEvent& event) override;

    //==============================================================================
    std::function<void (const int indexValue)> onClick;
    std::function<void (const int indexValue)> onDelete;

private:
    //==============================================================================
    Preset mPreset;

    Images mImages;
    Label mPresetLabel;
    PresetDeleteComponent mPresetDelete;

    DrawableButton mTrashButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetComponent)
};
