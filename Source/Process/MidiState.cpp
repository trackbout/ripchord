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

std::map<int, Output> MidiState::getCurrentlyOnOutputNotes()
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

void MidiState::setCurrentlyOnOutputNotes (std::map<int, Output> inOutputNotes)
{
    juce::Array<int> prevCurrentlyOnOutputNotes = getOutputNotesArray (mCurrentlyOnOutputNotes);
    juce::Array<int> nextCurrentlyOnOutputNotes = getWeightedOutputNotesArray (inOutputNotes);

    mCurrentlyOnOutputNotes.clear();
    mCurrentlyOnOutputNotes = inOutputNotes;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentlyOnOutputNotes;
    message->messageArray1 = prevCurrentlyOnOutputNotes;
    message->messageArray2 = nextCurrentlyOnOutputNotes;
    sendMessage (message, ListenerType::kAsync);
}

//==============================================================================
bool MidiState::containsOutputNoteTrigger (const int inOutputNote, const int inInputNote)
{
    if (mCurrentlyOnOutputNotes.count (inOutputNote) < 1) { return false; }
    auto pair = mCurrentlyOnOutputNotes.find (inOutputNote);
    juce::Array<int> triggers = pair->second.triggers;
    return triggers.indexOf (inInputNote) > -1;
}

const int MidiState::getOutputNoteTriggerCount (const int inOutputNote)
{
    if (mCurrentlyOnOutputNotes.count (inOutputNote) < 1) { return 0; }
    auto pair = mCurrentlyOnOutputNotes.find (inOutputNote);
    juce::Array<int> triggers = pair->second.triggers;
    return triggers.size();
}

//==============================================================================
void MidiState::setActiveTransposeNoteIfAllowed (const int inputNote)
{
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kActiveTransposeNoteAllowed;
    message->messageVar1 = inputNote;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
juce::Array<int> MidiState::getOutputNotesArray (std::map<int, Output> outputNotes)
{
    juce::Array<int> outputNotesArray;

    for (const auto& pair : outputNotes)
    {
      outputNotesArray.add (pair.first);
    }

    return outputNotesArray;
}

juce::Array<int> MidiState::getWeightedOutputNotesArray (std::map<int, Output> outputNotes)
{
    juce::Array<int> weightedOutputNotesArray;

    for (const auto& pair : outputNotes)
    {
        if (pair.second.triggers.size() == 2)
        {
            weightedOutputNotesArray.add ((pair.first) + DOUBLE_TRIGGER_WEIGHT);
        }
        else
        {
            weightedOutputNotesArray.add (pair.first);
        }
    }

    return weightedOutputNotesArray;
}
