#pragma once

#include "JuceHeader.h"

class DataMessageBroadcaster;

enum ListenerType
{
    kSync = 0,
    kAsync
};

enum MessageCode
{
    kGeneric = 0,

    // Messages from GlobalState
    kToggleTheme,
    kTogglePower,
    kToggleMode,
    kToggleView,
    kToggleRight,
    kToggleMenu,

    // Messages from ControlsState
    kToggleRecord,
    kDelayDepth,
    kDelayVariance,
    kDelayDirection,
    kVelocityDepth,
    kVelocityVariance,
    kVelocityDirection,
    kTransposeBase,
    kToggleTranspose,
    kActiveTransposeNote,

    // Messages from BrowserState
    kTagCreated,
    kTagDeleted,
    kTagShifted,
    kToggleTagManager,
    kToggleTagSelector,
    kClickPresetTagger,
    kClickAssignableTag,
    kClickSelectableTag,
    kToggleFavorites,
    kPresetFileDeleted,
    kPresetFileFavorited,
    kPresetFilterTextChanged,
    kCurrentIndexChanged,

    // Messages from PresetState
    kPresetFileNew,
    kPresetModified,
    kPresetFileSaved,
    kPresetFileLoaded,
    kEditModeInputNote,
    kEditModeOutputNotes,
    kEditModeShiftArrow,
    kChordNameTextChanged,
    kPresetNameTextChanged,

    // Messages from MidiState
    kIsRecording,
    kInputNoteOn,
    kInputNoteOff,
    kOutputNoteOn,
    kOutputNoteOff,
    kClearStuckNotes,
    kActiveTransposeNoteAllowed
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DataMessage);
};
