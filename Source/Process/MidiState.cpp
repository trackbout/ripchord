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

std::map<int, Origin> MidiState::getCurrentlyOnOutputNotes()
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
void MidiState::setActiveTransposeNoteIfAllowed (const int inputNote)
{
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kActiveTransposeNoteAllowed;
    message->messageVar1 = inputNote;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
juce::Array<NoteEvent> MidiState::getNoteEventsToSend()
{
    juce::Array<int> indexesToRemove;
    juce::Array<NoteEvent> notesToSend;

    for (int index = 0; index < mNoteEventQueu.size(); index++)
    {
        NoteEvent noteEvent = mNoteEventQueu.getUnchecked (index);

        if (noteEvent.timeToSend <= Time::getCurrentTime().toMilliseconds())
        {
            notesToSend.add (noteEvent);
            indexesToRemove.add (index);
        }
    }

    for (int index : indexesToRemove)
    {
        mNoteEventQueu.remove (index);
    }

    return notesToSend;
}

void MidiState::addNoteEventToQueu (NoteEvent inNoteEvent, int inIndexInChord, float inDelayDepth, float inDelayVariance)
{
    inNoteEvent.timeToSend = Time::getCurrentTime().toMilliseconds() + (inIndexInChord * 50);
    mNoteEventQueu.add (inNoteEvent);
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
