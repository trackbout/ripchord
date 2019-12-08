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

    // Allows us to add a message listener to this Broadcaster.
    // Listener types are -> 0: async, 1: sync
    void addListener (DataMessageListener* inListener, int inListenerType);

    // Allows us to send messages to corresponding message listeners.
    void sendMessage (DataMessage* inMessage, int inListenerType);

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessageBroadcaster);
};
