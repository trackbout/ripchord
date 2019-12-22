#pragma once

#include "JuceHeader.h"

struct Chord
{
    String chordName;
    Array<int> chordNotes;
};

//==============================================================================
class CurrentPresetState
{
public:
    //==============================================================================
    CurrentPresetState();
    ~CurrentPresetState();

    //==============================================================================
    String getPresetName();
    void setPresetName (String name);

    //==============================================================================
    Chord getPresetChord (const int inputNote);
    void setPresetChord (const int inputNote, Chord chord);

    //==============================================================================
    void resetPresetName();
    void resetPresetChords();

    //==============================================================================
    void addPresetChord (const int inputNote);
    void removePresetChord (const int inputNote);

    //==============================================================================
    void addPresetChordNote (const int inputNote, const int *outputNote);
    void removePresetChordNote (const int inputNote, const int *outputNote);

private:
    //==============================================================================
    String mPresetName;
    std::map<int, Chord> mPresetChords;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CurrentPresetState)
};
