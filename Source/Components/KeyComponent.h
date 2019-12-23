#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"

//==============================================================================
class KeyComponent : public Component
{
public:
    //==============================================================================
    KeyComponent (const int noteNumber);
    ~KeyComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;

    //==============================================================================
    const int getNoteNumber();

    //==============================================================================
    void mouseUp (const MouseEvent& event) override;
    void mouseDown (const MouseEvent& event) override;

protected:
    //==============================================================================
    Colour getDefaultColor();

private:
    //==============================================================================
    const int mNoteNumber;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyComponent)
};
