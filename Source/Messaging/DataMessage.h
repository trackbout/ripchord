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

enum MessageCode
{
    kGeneric = 0,

    // Messages from global state
    kModeUpdated,
    kViewUpdated,
    kMenuUpdated,

    // Messages from external midi keyboards
    kNoteOnExternal,
    kNoteOffExternal,

    // Messages from mouse clicks on the UI
    kNoteOnInternal,
    kNoteOffInternal,
    kSelectedEditNote
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
    MessageCode messageCode;

    int listenerType;
    var messageData0;
    var messageData1;
    var messageData2;

private:
    //==============================================================================

    //==============================================================================
    // TODO: figure out why this class leaks
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessage);
};
