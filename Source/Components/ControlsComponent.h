#pragma once

#include "JuceHeader.h"

//==============================================================================
class ControlsComponent : public Component
{
public:
    //==============================================================================
    ControlsComponent();
    ~ControlsComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;
    void resized() override;

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
