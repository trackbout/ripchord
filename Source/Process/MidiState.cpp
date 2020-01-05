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

std::map<int, juce::Array<int>> MidiState::getCurrentlyOnOutputNotes()
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
    sendMessage (message, ListenerType::kAsync);
}

void MidiState::setCurrentlyOnOutputNotes (std::map<int, juce::Array<int>> inOutputNotes)
{
    juce::Array<int> prevCurrentlyOnOutputNotes = getOutputNotesArray (mCurrentlyOnOutputNotes);
    juce::Array<int> nextCurrentlyOnOutputNotes = getOutputNotesArray (inOutputNotes);

    mCurrentlyOnOutputNotes.clear();
    mCurrentlyOnOutputNotes = inOutputNotes;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentlyOnOutputNotes;
    message->messageArray1 = prevCurrentlyOnOutputNotes;
    message->messageArray2 = nextCurrentlyOnOutputNotes;
    sendMessage (message, ListenerType::kAsync);
}

//==============================================================================
bool MidiState::containsCurrentlyOnOutputNote (const int inOutputNote)
{
    return mCurrentlyOnOutputNotes.count (inOutputNote) > 0;
}

bool MidiState::containsOutputNoteTrigger (const int inOutputNote, const int inInputNote)
{
    if (!containsCurrentlyOnOutputNote (inOutputNote)) { return false; }
    auto pair = mCurrentlyOnOutputNotes.find (inOutputNote);
    juce::Array<int> triggers = pair->second;
    return triggers.indexOf (inInputNote) > -1;
}

const int MidiState::getOutputNoteTriggerCount (const int inOutputNote, const int inInputNote)
{
    if (!containsCurrentlyOnOutputNote (inOutputNote)) { return 0; }
    auto pair = mCurrentlyOnOutputNotes.find (inOutputNote);
    juce::Array<int> triggers = pair->second;
    return triggers.size();
}

//==============================================================================
juce::Array<int> MidiState::getOutputNotesArray (std::map<int, juce::Array<int>> outputNotes)
{
    juce::Array<int> outputNotesArray;
    std::map<int, juce::Array<int>>::iterator pair;

    for (pair = outputNotes.begin(); pair != outputNotes.end(); ++pair)
    {
      outputNotesArray.add (pair->first);
    }

    return outputNotesArray;
}
