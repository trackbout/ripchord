#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"

//==============================================================================
class MenuComponent : public Component
{
public:
    //==============================================================================
    MenuComponent();
    ~MenuComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& event) override;
    std::function<void()> handleBackgroundClick;

private:
    //==============================================================================
    Images mImages;

    DrawableButton mNewButton { "", DrawableButton::ImageStretched };
    DrawableButton mImportButton { "", DrawableButton::ImageStretched };
    DrawableButton mExportButton { "", DrawableButton::ImageStretched };
    DrawableButton mCommunityButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuComponent)
};
