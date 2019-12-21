#include "ChordObject.h"

//==============================================================================
ChordObject::ChordObject()
{
}

ChordObject::~ChordObject()
{
}

//==============================================================================
String ChordObject::getChordName()
{
    return mChordName;
}

void ChordObject::setChordName (String inName)
{
    mChordName = inName;
}

//==============================================================================
Array<int> ChordObject::getChordNotes()
{
    return mChordNotes;
}

void ChordObject::setChordNotes (Array<int> inNotes)
{
    mChordNotes = inNotes;
}

//==============================================================================
void ChordObject::addChordNote (const int inNote)
{
    mChordNotes.add (inNote);
}

void ChordObject::removeChordNote (const int *inNote)
{
    mChordNotes.remove (inNote);
}
