#pragma once

#include "JuceHeader.h"
#include "Constants.h"
#include "Interface.h"
#include "MainProcess.h"

//==============================================================================
class KeyComponent : public Component
{
public:
    //==============================================================================
    KeyComponent (MainProcess&, int midiNoteNumber);
    ~KeyComponent();

    //==============================================================================
    void paint (Graphics& graphics) override;

    //==============================================================================
    int getMidiNoteNumber();

    //==============================================================================
    void mouseUp (const MouseEvent& event) override;
    void mouseDown (const MouseEvent& event) override;

protected:
    //==============================================================================
    Colour getDefaultColor();

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    CurrentPresetState& mCurrentPresetState;

    //==============================================================================
    int mMidiNoteNumber;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyComponent)
};
