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

//==============================================================================
void PresetState::setEditModeInputNote (const int inInputNote)
{
    const int prevEditModeInputNote = mEditModeInputNote;
    const int nextEditModeInputNote = inInputNote == mEditModeInputNote ? 0 : inInputNote;
    juce::Array<int> prevEditModeOutputNotes = getPresetChord (prevEditModeInputNote).chordNotes;
    juce::Array<int> nextEditModeOutputNotes = getPresetChord (nextEditModeInputNote).chordNotes;

    mEditModeInputNote = nextEditModeInputNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kEditModeInputNote;
    message->messageVar1 = prevEditModeInputNote;
    message->messageVar2 = nextEditModeInputNote;
    message->messageArray1 = prevEditModeOutputNotes;
    message->messageArray2 = nextEditModeOutputNotes;
    sendMessage (message, ListenerType::kSync);
}

void PresetState::setEditModeOutputNote (const int inOutputNote)
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
