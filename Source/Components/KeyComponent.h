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

protected:
    //==============================================================================
    Colour getDefaultColor();

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;

    //==============================================================================
    int mMidiNoteNumber;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyComponent)
};
