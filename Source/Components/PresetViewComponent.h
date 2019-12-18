#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "Images.h"
#include "MainProcess.h"
#include "PresetListComponent.h"

//==============================================================================
class PresetViewComponent : public Component
{
public:
    //==============================================================================
    PresetViewComponent (MainProcess&);
    ~PresetViewComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    Images mImages;
    Viewport mPresetViewport;
    TextEditor mPresetFilterInput;
    PresetListComponent mPresetListComponent;

    DrawableButton mFavoritesButton { "", DrawableButton::ImageStretched };
    DrawableButton mKeyboardsButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewComponent)
};
