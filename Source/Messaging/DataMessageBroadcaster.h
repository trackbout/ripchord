#pragma once

#include "JuceHeader.h"

class DataMessageListener;
class DataMessage;

//==============================================================================
class DataMessageBroadcaster
{
public:
    //==============================================================================
    DataMessageBroadcaster();
    ~DataMessageBroadcaster();

    // Allows us to add a message listener. Types are -> 0: async, 1: sync
    void addListener (DataMessageListener* listener, int listenerType);

    // Allows us to send messages to corresponding message listeners.
    void sendMessage (DataMessage* message, int listenerType);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessageBroadcaster);
};
