#pragma once

#include "JuceHeader.h"
#include "DataMessageListener.h"

//==============================================================================
class MainProcess : private DataMessageListener
{
public:
    //==============================================================================
    MainProcess();
    ~MainProcess();

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainProcess)
};
