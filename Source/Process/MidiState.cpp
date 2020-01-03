#include "MidiState.h"

//==============================================================================
MidiState::MidiState()
{
}

MidiState::~MidiState()
{
}

//==============================================================================
juce::Array<int> MidiState::getCurrentlyOnInputNotes()
{
    return mCurrentlyOnInputNotes;
}

std::map<int, int> MidiState::getCurrentlyOnOutputNotes()
{
    return mCurrentlyOnOutputNotes;
}

//==============================================================================
void MidiState::setCurrentlyOnInputNotes (juce::Array<int> inInputNotes)
{
    mCurrentlyOnInputNotes.clear();
    mCurrentlyOnInputNotes = inInputNotes;
}

void MidiState::setCurrentlyOnOutputNotes (std::map<int, int> inOutputNotes)
{
    mCurrentlyOnOutputNotes.clear();
    mCurrentlyOnOutputNotes = inOutputNotes;
}

//==============================================================================
bool MidiState::containsCurrentlyOnOutputNote (const int inOutputNote)
{
    return mCurrentlyOnOutputNotes.count (inOutputNote) > 0;
}

bool MidiState::wasOutputNoteTriggeredByInputNote (const int inOutputNote, const int inInputNote)
{
    if (!containsCurrentlyOnOutputNote (inOutputNote)) { return false; }
    auto pair = mCurrentlyOnOutputNotes.find (inOutputNote);
    return inInputNote == pair->second;
}
