#pragma once

#include "JuceHeader.h"

class DataMessageBroadcaster;
class DataMessageListener;
class DataMessage;

//==============================================================================
class DataMessageManager : public DeletedAtShutdown
{
public:
    //==============================================================================
    DataMessageManager();
    ~DataMessageManager();

    // Allows us to connect a message listener to a message broadcaster, for a given "listener type"
    void addListener (DataMessageListener* inListener, DataMessageBroadcaster* inBroadcaster, int inListenerType);

    void removeListener (DataMessageListener* inListener);

    void sendMessageToListeners (DataMessageBroadcaster* inBroadcaster, DataMessage* inMessage, int inListenerType);

    // Second arg of "false" allows the instance to be recreated if needed
    juce_DeclareSingleton (DataMessageManager, false);

private:
    //==============================================================================

    // Internal
    void updateSyncListeners (DataMessageBroadcaster* inBroadcaster, DataMessage* inMessage);

    // Internal
    void updateAsyncListeners (DataMessageBroadcaster* inBroadcaster, DataMessage* inMessage);

    std::multimap<DataMessageBroadcaster*, DataMessageListener*> mSyncListeners;

    std::multimap<DataMessageBroadcaster*, DataMessageListener*> mAsyncListeners;

    CriticalSection mListenerLock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessageManager);
};
