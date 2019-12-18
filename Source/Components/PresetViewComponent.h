#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "Images.h"
#include "PresetListComponent.h"

//==============================================================================
class PresetViewComponent : public Component
{
public:
    //==============================================================================
    PresetViewComponent();
    ~PresetViewComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    Images mImages;
    Viewport mPresetViewport;
    TextEditor mPresetFilterInput;
    PresetListComponent mPresetListComponent;

    DrawableButton mFavoritesButton { "", DrawableButton::ImageStretched };
    DrawableButton mKeyboardsButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewComponent)
};
