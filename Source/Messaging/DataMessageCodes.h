#pragma once

enum DataMessageCode
{
    kGeneric = 0,

    // Messages from mouse clicks on the UI
    kMidiNoteOnInternal,
    kMidiNoteOffInternal,

    // Messages from external midi keyboards
    kMidiNoteOnExternal,
    kMidiNoteOffExternal,

    // Messages from KeyboardState
    kKeyboardStateUpdated,

    // Messages from a Chord object
    kChordStateUpdated,

    // Messages from MappingState
    kMappingStateUpdated,
};
