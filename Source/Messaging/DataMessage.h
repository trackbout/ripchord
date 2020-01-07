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

    // Messages from GlobalState
    kModeUpdated,
    kViewUpdated,
    kMenuUpdated,

    // Messages from PresetState
    kPresetNameUpdated,
    kEditModeInputNote,
    kEditModeOutputNotes,

    // Messages from MidiState
    kCurrentlyOnInputNotes,
    kCurrentlyOnOutputNotes
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
    var messageVar1;
    var messageVar2;
    var messageVar3;
    var messageVar4;
    juce::Array<int> messageArray1;
    juce::Array<int> messageArray2;

private:
    //==============================================================================

    //==============================================================================
    // TODO: figure out why this class leaks
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessage);
};
