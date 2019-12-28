#include "PresetState.h"

//==============================================================================
PresetState::PresetState()
{
}

PresetState::~PresetState()
{
}

//==============================================================================
String PresetState::getPresetName()
{
    return mPresetName;
}

void PresetState::setPresetName (String inName)
{
    mPresetName = inName;
}

//==============================================================================
Chord PresetState::getPresetChord (const int inInputNote)
{
    return mPresetChords[inInputNote];
}

void PresetState::setPresetChord (const int inInputNote, Chord inChord)
{
    mPresetChords[inInputNote] = inChord;
}

//==============================================================================
void PresetState::resetPresetName()
{
    mPresetName = "";
}

void PresetState::resetPresetChords()
{
    mPresetChords.clear();
}

//==============================================================================
void PresetState::addPresetChord (const int inInputNote)
{
    Chord newChord;
    mPresetChords[inInputNote] = newChord;
}

void PresetState::removePresetChord (const int inInputNote)
{
    mPresetChords.erase (inInputNote);
}

bool PresetState::containsPresetChord (const int inInputNote)
{
    return mPresetChords.count (inInputNote) > 0;
}

//==============================================================================
void PresetState::addPresetChordNote (const int inInputNote, const int inOutputNote)
{
    Chord presetChord = mPresetChords[inInputNote];
    presetChord.chordNotes.add (inOutputNote);
}

void PresetState::removePresetChordNote (const int inInputNote, const int *inOutputNote)
{
    Chord presetChord = mPresetChords[inInputNote];
    presetChord.chordNotes.remove (*inOutputNote);
}

bool PresetState::containsPresetChordNote (const int inInputNote, const int inOutputNote)
{
    if (!containsPresetChord (inInputNote)) { return false; }

    Chord presetChord = getPresetChord (inInputNote);
    Array<int> notes = presetChord.chordNotes;
    return std::find (std::begin(notes), std::end(notes), inOutputNote) != std::end(notes);
}

//==============================================================================
int PresetState::getSelectedEditNote()
{
    return mSelectedEditNote;
}

void PresetState::setSelectedEditNote (int inNoteNumber)
{
    const int prevSelectedEditNote = mSelectedEditNote;
    const int nextSelectedEditNote = inNoteNumber == mSelectedEditNote ? 0 : inNoteNumber;
    mSelectedEditNote = nextSelectedEditNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kSelectedEditNote;
    message->messageData0 = prevSelectedEditNote;
    message->messageData1 = nextSelectedEditNote;
    sendMessage (message, ListenerType::kSync);
}
