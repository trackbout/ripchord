#include "DataMessageBroadcaster.h"
#include "DataMessageManager.h"
#include "DataMessage.h"

//==============================================================================
DataMessageBroadcaster::DataMessageBroadcaster()
{
}

DataMessageBroadcaster::~DataMessageBroadcaster()
{
}

//==============================================================================
void DataMessageBroadcaster::addListener (DataMessageListener* inListener, int inListenerType)
{
    if (inListenerType == ListenerType::kSyncAsync)
    {
        // A Broadcaster can be "syncAsync".
        // A Listener can only be either "sync", or "async".
        jassertfalse;
    }

    // Call message manager, connect broadcaster to listener for given 'listener type'
    DataMessageManager::getInstance()->addListener (inListener, this, inListenerType);
}

void DataMessageBroadcaster::sendMessage (DataMessage* inMessage, int inListenerType)
{
    // Set "this" object as broadcaster
    inMessage->broadcaster = this;

    // Set the "type" of listener (sync / async)
    inMessage->listenerType = inListenerType;

    // send message through the manager
    DataMessageManager::getInstance()->sendMessageToListeners (this, inMessage, inListenerType);
}
