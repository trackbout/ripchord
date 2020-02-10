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

juce::Array<int> MidiState::getOutputNoteTriggers (const int inOutputNote)
{
    juce::Array<int> triggers;
    if (mCurrentlyOnOutputNotes.count (inOutputNote) < 1) { return triggers; }
    auto pair = mCurrentlyOnOutputNotes.find (inOutputNote);
    triggers = pair->second.triggers;
    return triggers;
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

void MidiState::setOutputNoteOn (int inOutputNote, juce::Array<int>& inTriggers)
{
    mCurrentlyOnOutputNotes[inOutputNote].triggers = inTriggers;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kOutputNoteOn;
    message->messageVar1 = inOutputNote;
    message->messageArray1 = inTriggers;
    sendMessage (message, ListenerType::kAsync);
}

void MidiState::setOutputNoteOff (int inOutputNote, juce::Array<int>& inTriggers)
{
    if (inTriggers.size() == 1) { mCurrentlyOnOutputNotes[inOutputNote].triggers = inTriggers; }
    if (inTriggers.size() == 0) { mCurrentlyOnOutputNotes.erase (inOutputNote); }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kOutputNoteOff;
    message->messageVar1 = inOutputNote;
    message->messageArray1 = inTriggers;
    sendMessage (message, ListenerType::kAsync);
}

//==============================================================================
void MidiState::setActiveTransposeNoteIfAllowed (const int inputNote)
{
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kActiveTransposeNoteAllowed;
    message->messageVar1 = inputNote;
    sendMessage (message, ListenerType::kSync);
}

void MidiState::addNoteEventToQueu (NoteEvent inNoteEvent, int inIndexInChord, float inDelayDepth, float inDelayVariance)
{
    inNoteEvent.timeToSend = Time::getCurrentTime().toMilliseconds() + (inIndexInChord * 50);
    mNoteEventQueu.add (inNoteEvent);
}

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
