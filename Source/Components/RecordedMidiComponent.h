#pragma once

#include "JuceHeader.h"

//==============================================================================
class RecordedMidiComponent : public Component, public DragAndDropContainer
{
public:
    //==============================================================================
    RecordedMidiComponent();
    ~RecordedMidiComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecordedMidiComponent)
};
