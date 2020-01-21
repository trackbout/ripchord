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
    void toggleTranspose();
    bool isTransposeOff();
    bool isTransposeOn();
    bool isTransposeLocked();

private:
    //==============================================================================
    Transpose mTranspose = Transpose::Off;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
