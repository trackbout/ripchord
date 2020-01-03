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
    juce::Array<int> prevCurrentlyOnInputNotes = mCurrentlyOnInputNotes;
    juce::Array<int> nextCurrentlyOnInputNotes = inInputNotes;

    mCurrentlyOnInputNotes.clear();
    mCurrentlyOnInputNotes = nextCurrentlyOnInputNotes;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentlyOnInputNotes;
    message->messageArray1 = prevCurrentlyOnInputNotes;
    message->messageArray2 = nextCurrentlyOnInputNotes;
    sendMessage (message, ListenerType::kSync);
}

void MidiState::setCurrentlyOnOutputNotes (std::map<int, int> inOutputNotes)
{
    juce::Array<int> prevCurrentlyOnOutputNotes = getOutputNotesArray (mCurrentlyOnOutputNotes);
    juce::Array<int> nextCurrentlyOnOutputNotes = getOutputNotesArray (inOutputNotes);

    mCurrentlyOnOutputNotes.clear();
    mCurrentlyOnOutputNotes = inOutputNotes;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentlyOnOutputNotes;
    message->messageArray1 = prevCurrentlyOnOutputNotes;
    message->messageArray2 = nextCurrentlyOnOutputNotes;
    sendMessage (message, ListenerType::kSync);
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

//==============================================================================
juce::Array<int> MidiState::getOutputNotesArray (std::map<int, int> outputNotes)
{
    juce::Array<int> outputNotesKeys;
    std::map<int, int>::iterator pair;

    for (pair = outputNotes.begin(); pair != outputNotes.end(); ++pair)
    {
      outputNotesKeys.add (pair->first);
    }

    return outputNotesKeys;
}
