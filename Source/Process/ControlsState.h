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
    enum Transpose { Off = 0, On, Locked };

    //==============================================================================
    bool isTransposeOff();
    bool isTransposeOn();
    bool isTransposeLocked();

    //==============================================================================
    int getTransposeBase();
    bool isTransposeKey (const int inputNote);

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
