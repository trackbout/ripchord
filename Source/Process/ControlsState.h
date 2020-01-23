#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class ControlsState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    ControlsState();
    ~ControlsState();

    //==============================================================================
    enum Transpose { Off, Enabled, Latched };

    //==============================================================================
    bool isTransposeOff();
    bool isTransposeEnabled();
    bool isTransposeLatched();

    //==============================================================================
    int getTransposeBase();
    bool isTransposeNote (const int inputNote);

    //==============================================================================
    void toggleTranspose();
    void handleMouseClickOnShiftLeft();
    void handleMouseClickOnShiftRight();

private:
    //==============================================================================
    int mTransposeBase = 21;
    Transpose mTranspose = Transpose::Off;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
