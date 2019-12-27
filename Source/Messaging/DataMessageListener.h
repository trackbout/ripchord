#pragma once

#include "JuceHeader.h"

class DataMessage;

//==============================================================================
class DataMessageListener
{
public:
    //==============================================================================
    DataMessageListener();
    virtual ~DataMessageListener();

    //==============================================================================
    virtual void handleNewMessage (const DataMessage* message) = 0;

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessageListener);
};
