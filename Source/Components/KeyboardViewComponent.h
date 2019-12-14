#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "Images.h"
#include "KeyboardComponent.h"

//==============================================================================
class KeyboardViewComponent : public Component
{
public:
    //==============================================================================
    KeyboardViewComponent();
    ~KeyboardViewComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    Label mOutputKeyboardLabel { "", "output" };
    Label mInputKeyboardLabel { "", "input" };

    KeyboardComponent mOutputKeyboard;
    KeyboardComponent mInputKeyboard;

    Images mImages;
    DrawableButton mModeButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardViewComponent)
};
