#pragma once

#include "JuceHeader.h"

class DataMessageBroadcaster;

// Never add a 'syncAsync' listener, a listener only needs one type.
// The 'syncAsync' type exists for broadcasters, to broadcast a single message to multiple listener types.
enum ListenerType
{
    kSync = 0,
    kAsync,
    kSyncAsync
};

enum DataMessageCode
{
    kGeneric = 0,

    // Messages from global state
    kModeUpdated,
    kViewUpdated,
    kMenuUpdated,

    // Messages from mouse clicks on the UI
    kMidiNoteOnInternal,
    kMidiNoteOffInternal,

    // Messages from external midi keyboards
    kMidiNoteOnExternal,
    kMidiNoteOffExternal
};

//==============================================================================
class DataMessage : public Message
{
public:
    //==============================================================================
    DataMessage();
    ~DataMessage();

    //==============================================================================
    DataMessageBroadcaster* broadcaster;
    DataMessageCode messageCode;

    int listenerType;
    var messageData0;
    var messageData1;
    var messageData2;

private:
    //==============================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessage);
};
