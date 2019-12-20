#include "DataMessageManager.h"
#include "DataMessageBroadcaster.h"
#include "DataMessageListener.h"
#include "DataMessage.h"

juce_ImplementSingleton (DataMessageManager);

//==============================================================================
DataMessageManager::DataMessageManager()
{
}

DataMessageManager::~DataMessageManager()
{
    clearSingletonInstance();
}

void DataMessageManager::addListener (DataMessageListener* inListener,
                                      DataMessageBroadcaster* inBroadcaster,
                                      int inListenerType)
{
    const CriticalSection::ScopedLockType lock (mListenerLock);

    std::pair<DataMessageBroadcaster*, DataMessageListener*> listener_pair (inBroadcaster, inListener);

    switch (inListenerType)
    {
        case (ListenerType::kSync):
        {
            mSyncListeners.insert (listener_pair);
        } break;

        case (ListenerType::kAsync):
        {
            mAsyncListeners.insert (listener_pair);
        } break;
    };
}

void DataMessageManager::removeListener (DataMessageListener* inListener)
{
    const CriticalSection::ScopedLockType lock (mListenerLock);

    // Remove Sync Listeners
    std::multimap<DataMessageBroadcaster*, DataMessageListener*>::iterator sync_pair = mSyncListeners.begin();

    while (sync_pair != mSyncListeners.end())
    {
        if (sync_pair->second == inListener)
        {
            mSyncListeners.erase(sync_pair);
            sync_pair = mSyncListeners.begin();
        }

        else
        {
            ++sync_pair;
        }
    }

    // Remove Async Listeners
    std::multimap<DataMessageBroadcaster*, DataMessageListener*>::iterator async_pair = mAsyncListeners.begin();

    while (async_pair != mAsyncListeners.end())
    {
        if (async_pair->second == inListener)
        {
            mAsyncListeners.erase(async_pair);
            async_pair = mAsyncListeners.begin();
        }

        else
        {
            ++async_pair;
        }
    }
}

void DataMessageManager::sendMessageToListeners (DataMessageBroadcaster* inBroadcaster,
                                                 DataMessage* inMessage,
                                                 int inListenerType)
{   
    std::multimap<DataMessageBroadcaster*, DataMessageListener*> store;

    switch (inListenerType)
    {
        case (ListenerType::kSync):
        {
            updateSyncListeners (inBroadcaster, inMessage);
        } break;

        case (ListenerType::kAsync):
        {
            updateAsyncListeners (inBroadcaster, inMessage);
        } break;

        case (ListenerType::kSyncAsync):
        {
            updateSyncListeners (inBroadcaster, inMessage);
            updateAsyncListeners (inBroadcaster, inMessage);
        } break;

        default: {
            jassertfalse;
        } break;
    };
}

void DataMessageManager::updateSyncListeners (DataMessageBroadcaster* inBroadcaster, DataMessage* inMessage)
{
    std::multimap<DataMessageBroadcaster*, DataMessageListener*>::iterator pair = mSyncListeners.begin();

    while (pair != mSyncListeners.end())
    {
        if (pair->first == inBroadcaster)
        {
            pair->second->messageReceived(inMessage);
        }

        ++pair;
    }
}

void DataMessageManager::updateAsyncListeners (DataMessageBroadcaster* inBroadcaster, DataMessage* inMessage)
{
    MessageManager::callAsync ([this, inBroadcaster, inMessage](){

        std::multimap<DataMessageBroadcaster*, DataMessageListener*>::iterator pair = mAsyncListeners.begin();

        while (pair != mAsyncListeners.end())
        {
            if (pair->first == inBroadcaster)
            {
                pair->second->messageReceived(inMessage);
            }

            ++pair;
        }
    });
}
