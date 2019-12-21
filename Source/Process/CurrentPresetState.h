#pragma once

#include "JuceHeader.h"

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

private:
    //==============================================================================
    struct Chord
    {
        String chordName;
        Array<int> chordNotes;
    };

    //==============================================================================
    String mPresetName;
    std::map<int, Chord> mPresetChords;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CurrentPresetState)
};
