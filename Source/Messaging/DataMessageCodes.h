#pragma once

enum DataMessageCode
{
    kGeneric = 0,
    
    // Messages from global state
    kModeUpdated,

    // Messages from mouse clicks on the UI
    kMidiNoteOnInternal,
    kMidiNoteOffInternal,

    // Messages from external midi keyboards
    kMidiNoteOnExternal,
    kMidiNoteOffExternal,
};
