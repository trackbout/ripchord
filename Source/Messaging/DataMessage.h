#pragma once

#include "JuceHeader.h"
#include "DataMessageCodes.h"

class DataMessageBroadcaster;

// Never add a 'syncAsync' listener, a listener only needs one type.
// The 'syncAsync' type exists for broadcasters, to broadcast a single message to multiple listener types.
enum
{
    kListenerType_Sync = 0,
    kListenerType_Async,
    kListenerType_SyncAsync
};

//==============================================================================
class DataMessage : public Message
{
public:
    //==============================================================================
    DataMessage();
    ~DataMessage();

    DataMessageCode messageCode;
    var messageData0;
    var messageData1;
    var messageData2;

    int listenerType;
    DataMessageBroadcaster* broadcaster;
};
