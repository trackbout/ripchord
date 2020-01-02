#include "PresetState.h"

//==============================================================================
PresetState::PresetState()
{
}

PresetState::~PresetState()
{
}

//==============================================================================
void PresetState::resetEditModeInputNote()
{
    mEditModeInputNote = 0;
}

const int PresetState::getEditModeInputNote()
{
    return mEditModeInputNote;
}

juce::Array<int> PresetState::getMappedInputNotes()
{
    juce::Array<int> mappedInputNotes;
    std::map<int, Chord>::iterator pair;

    for (pair = mPresetChords.begin(); pair != mPresetChords.end(); ++pair) {
      mappedInputNotes.add (pair->first);
    }

    return mappedInputNotes;
}

//==============================================================================
void PresetState::handleEditModeMouseDownOnInput (const int inInputNote)
{
    const int prevEditModeInputNote = mEditModeInputNote;
    const int nextEditModeInputNote = inInputNote == mEditModeInputNote ? 0 : inInputNote;
    bool prevEditModeInputNoteHasMarker = containsPresetChord (prevEditModeInputNote);
    juce::Array<int> prevEditModeOutputNotes = getPresetChord (prevEditModeInputNote).chordNotes;
    juce::Array<int> nextEditModeOutputNotes = getPresetChord (nextEditModeInputNote).chordNotes;

    mEditModeInputNote = nextEditModeInputNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeInputNote;
    message->messageVar1 = prevEditModeInputNote;
    message->messageVar2 = nextEditModeInputNote;
    message->messageVar3 = prevEditModeInputNoteHasMarker;
    message->messageArray1 = prevEditModeOutputNotes;
    message->messageArray2 = nextEditModeOutputNotes;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::handleEditModeMouseDownOnOutput (const int inOutputNote)
{
    juce::Array<int> prevEditModeOutputNotes = getPresetChord (mEditModeInputNote).chordNotes;
    bool shouldAddNote = !prevEditModeOutputNotes.contains (inOutputNote);

    if (shouldAddNote)
    {
        if (!containsPresetChord (mEditModeInputNote)) { addPresetChord (mEditModeInputNote); }
        Chord presetChord = getPresetChord (mEditModeInputNote);
        presetChord.chordNotes.add (inOutputNote);
        setPresetChord (mEditModeInputNote, presetChord);
    }

    else
    {
        if (prevEditModeOutputNotes.size() > 1)
        {
            Chord presetChord = getPresetChord (mEditModeInputNote);
            presetChord.chordNotes.removeFirstMatchingValue (inOutputNote);
            setPresetChord (mEditModeInputNote, presetChord);
        }

        else
        {
            removePresetChord (mEditModeInputNote);
        }
    }

    juce::Array<int> nextEditModeOutputNotes = getPresetChord (mEditModeInputNote).chordNotes;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeOutputNotes;
    message->messageArray1 = prevEditModeOutputNotes;
    message->messageArray2 = nextEditModeOutputNotes;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
Chord PresetState::getPresetChord (const int inInputNote)
{
    auto pair = mPresetChords.find (inInputNote);
    if (pair == mPresetChords.end()) { return mEmptyChord; }
    return pair->second;
}

void PresetState::setPresetChord (const int inInputNote, Chord inChord)
{
    mPresetChords[inInputNote] = inChord;
}

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
