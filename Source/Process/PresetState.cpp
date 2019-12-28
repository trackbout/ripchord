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

    Array<int> emptyChordNotes;
    bool prevInputContainsChord = containsPresetChord (prevEditModeInputNote);
    bool nextInputContainsChord = containsPresetChord (nextEditModeInputNote);
    Chord prevInputPresetChord = getPresetChord (prevEditModeInputNote);
    Chord nextInputPresetChord = getPresetChord (nextEditModeInputNote);
    Array<int> prevInputChordNotes = prevInputContainsChord ? prevInputPresetChord.chordNotes : emptyChordNotes;
    Array<int> nextInputChordNotes = nextInputContainsChord ? nextInputPresetChord.chordNotes : emptyChordNotes;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeInputNote;
    message->messageVar1 = prevEditModeInputNote;
    message->messageVar2 = nextEditModeInputNote;
    message->messageVar3 = prevInputContainsChord;
    message->messageVar4 = nextInputContainsChord;
    message->messageArray1 = prevInputChordNotes;
    message->messageArray2 = nextInputChordNotes;
    sendMessage (message, ListenerType::kSync);
}
