#include "CurrentPresetState.h"

//==============================================================================
CurrentPresetState::CurrentPresetState()
{
}

CurrentPresetState::~CurrentPresetState()
{
}

//==============================================================================
String CurrentPresetState::getPresetName()
{
    return mPresetName;
}

void CurrentPresetState::setPresetName (String inName)
{
    mPresetName = inName;
}

//==============================================================================
Chord CurrentPresetState::getPresetChord (const int inInputNote)
{
    return mPresetChords[inInputNote];
}

void CurrentPresetState::setPresetChord (const int inInputNote, Chord inChord)
{
    mPresetChords[inInputNote] = inChord;
}

//==============================================================================
void CurrentPresetState::resetPresetName()
{
    mPresetName = "";
}

void CurrentPresetState::resetPresetChords()
{
    mPresetChords.clear();
}

//==============================================================================
void CurrentPresetState::addPresetChord (const int inInputNote)
{
    Chord newChord;
    mPresetChords[inInputNote] = newChord;
}

void CurrentPresetState::removePresetChord (const int inInputNote)
{
    mPresetChords.erase (inInputNote);
}

bool CurrentPresetState::containsPresetChord (const int inInputNote)
{
    return mPresetChords.count (inInputNote) > 0;
}

//==============================================================================
void CurrentPresetState::addPresetChordNote (const int inInputNote, const int inOutputNote)
{
    Chord presetChord = mPresetChords[inInputNote];
    presetChord.chordNotes.add (inOutputNote);
}

void CurrentPresetState::removePresetChordNote (const int inInputNote, const int *inOutputNote)
{
    Chord presetChord = mPresetChords[inInputNote];
    presetChord.chordNotes.remove (*inOutputNote);
}

bool CurrentPresetState::containsPresetChordNote (const int inInputNote, const int inOutputNote)
{
    if (!containsPresetChord (inInputNote)) { return false; }

    Chord presetChord = getPresetChord (inInputNote);
    Array<int> notes = presetChord.chordNotes;
    return std::find (std::begin(notes), std::end(notes), inOutputNote) != std::end(notes);
}
