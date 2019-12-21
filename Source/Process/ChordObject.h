#pragma once

#include "JuceHeader.h"

//==============================================================================
class ChordObject
{
public:
    //==============================================================================
    ChordObject();
    ~ChordObject();

    //==============================================================================
    String getChordName();
    void setChordName (String name);

    //==============================================================================
    Array<int> getChordNotes();
    void setChordNotes (Array<int> notes);

    //==============================================================================
    void addChordNote (const int note);
    void removeChordNote (const int *note);

private:
    //==============================================================================
    String mChordName;
    Array<int> mChordNotes;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChordObject)
};
