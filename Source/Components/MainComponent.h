#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "KeyboardViewComponent.h"

//==============================================================================
class MainComponent : public Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    Label mTitleLabel { "", "ripchord" };
    KeyboardViewComponent mKeyboardViewComponent;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
