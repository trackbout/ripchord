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
    void addListener (DataMessageListener* listener, DataMessageBroadcaster* broadcaster, int listenerType);
    void removeListener (DataMessageListener* listener);
    void sendMessageToListeners (DataMessageBroadcaster* broadcaster, DataMessage* message, int listenerType);

    // Second arg of "false" allows the instance to be recreated if needed
    juce_DeclareSingleton (DataMessageManager, false);

private:
    //==============================================================================
    void updateSyncListeners (DataMessageBroadcaster* broadcaster, DataMessage* message);
    void updateAsyncListeners (DataMessageBroadcaster* broadcaster, DataMessage* message);

    std::multimap<DataMessageBroadcaster*, DataMessageListener*> mSyncListeners;
    std::multimap<DataMessageBroadcaster*, DataMessageListener*> mAsyncListeners;

    CriticalSection mListenerLock;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessageManager);
};
