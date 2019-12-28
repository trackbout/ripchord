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
int PresetState::getEditModeInputNote()
{
    return mEditModeInputNote;
}

void PresetState::setEditModeInputNote (int inInputNote)
{
    const int prevEditModeInputNote = mEditModeInputNote;
    const int nextEditModeInputNote = inInputNote == mEditModeInputNote ? 0 : inInputNote;
    mEditModeInputNote = nextEditModeInputNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeInputNote;
    message->messageData1 = prevEditModeInputNote;
    message->messageData2 = nextEditModeInputNote;
    sendMessage (message, ListenerType::kSync);
}
