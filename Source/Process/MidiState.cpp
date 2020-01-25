#include "MidiState.h"

//==============================================================================
MidiState::MidiState()
{
}

MidiState::~MidiState()
{
}

//==============================================================================
int MidiState::getCurrentlyOnTransposeNote()
{
    return mCurrentlyOnTransposeNote;
}

juce::Array<int> MidiState::getCurrentlyOnInputNotes()
{
    return mCurrentlyOnInputNotes;
}

std::map<int, Origin> MidiState::getCurrentlyOnOutputNotes()
{
    return mCurrentlyOnOutputNotes;
}

//==============================================================================
void MidiState::setCurrentlyOnTransposeNote (const int inInputNote)
{
    const int prevCurrentlyOnTransposeNote = mCurrentlyOnTransposeNote;
    const int nextCurrentlyOnTransposeNote = inInputNote;

    mCurrentlyOnTransposeNote = nextCurrentlyOnTransposeNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kCurrentlyOnTransposeNote;
    message->messageVar1 = prevCurrentlyOnTransposeNote;
    message->messageVar2 = nextCurrentlyOnTransposeNote;
    sendMessage (message, ListenerType::kAsync);
}

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

void MidiState::setCurrentlyOnOutputNotes (std::map<int, Origin> inOutputNotes)
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
juce::Array<int> MidiState::getOutputNotesArray (std::map<int, Origin> outputNotes)
{
    juce::Array<int> outputNotesArray;

    for (const auto& pair : outputNotes)
    {
      outputNotesArray.add (pair.first);
    }

    return outputNotesArray;
}

juce::Array<int> MidiState::getWeightedOutputNotesArray (std::map<int, Origin> outputNotes)
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
