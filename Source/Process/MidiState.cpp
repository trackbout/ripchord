#include "MidiState.h"

//==============================================================================
MidiState::MidiState()
{
}

MidiState::~MidiState()
{
}

//==============================================================================
int MidiState::getCurrentChannel()
{
    return mCurrentChannel;
}

void MidiState::setCurrentChannel (int inChannel)
{
    mCurrentChannel = inChannel;
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
void MidiState::setInputNoteOn (int inInputNote)
{
    mCurrentlyOnInputNotes.addIfNotAlreadyThere (inInputNote);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kInputNoteOn;
    message->messageVar1 = inInputNote;
    sendMessage (message, ListenerType::kAsync);
}

void MidiState::setInputNoteOff (int inInputNote)
{
    mCurrentlyOnInputNotes.removeFirstMatchingValue (inInputNote);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kInputNoteOff;
    message->messageVar1 = inInputNote;
    sendMessage (message, ListenerType::kAsync);
}

//==============================================================================
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

void MidiState::addNoteEventToQueue (NoteEvent inNoteEvent, int inIndexInChord, float inDelayDepth, float inDelayVariance)
{
    int delayVarianceMS = inDelayVariance * (rand() % 100 + 1);
    int delayDepthMS = inDelayDepth * MAX_DELAY_DEPTH_MS * inIndexInChord;
    inNoteEvent.timeToSend = Time::getCurrentTime().toMilliseconds() + delayDepthMS + delayVarianceMS;
    mNoteEventQueue.push (inNoteEvent);
}

bool MidiState::timeToSendNextNoteEvent()
{
    if (mNoteEventQueue.size() == 0) { return false; }
    if (mNoteEventQueue.front().timeToSend > Time::getCurrentTime().toMilliseconds()) { return false; }

    if (!mCurrentlyOnInputNotes.contains (mNoteEventQueue.front().inputNote))
    {
        mNoteEventQueue.pop();
        return false;
    }

    return true;
}

NoteEvent MidiState::getNextNoteEvent()
{
    NoteEvent noteEvent = mNoteEventQueue.front();
    mNoteEventQueue.pop();
    return noteEvent;
}

//==============================================================================
bool MidiState::hasStuckNotes()
{
    if (mCurrentlyOnOutputNotes.size() == 0) { return false; }
    if (mCurrentlyOnInputNotes.size() > 0) { return false; }
    return true;
}

juce::Array<int> MidiState::clearStuckNotes()
{
    juce::Array<int> stuckNotes;
    std::queue<NoteEvent> emptyQueue;

    for (const auto& pair : mCurrentlyOnOutputNotes)
    {
      stuckNotes.add (pair.first);
    }

    mCurrentlyOnOutputNotes.clear();
    std::swap (mNoteEventQueue, emptyQueue);

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kClearStuckNotes;
    sendMessage (message, ListenerType::kAsync);

    return stuckNotes;
}

void MidiState::clearAbortedNoteEvents (int inInputNote)
{
    bool hasAbortedNoteEvents = mNoteEventQueue.size() > 0;

    while (hasAbortedNoteEvents)
    {
        if (mNoteEventQueue.front().inputNote == inInputNote && mNoteEventQueue.size() > 0)
        {
            mNoteEventQueue.pop();
        }
        else
        {
            hasAbortedNoteEvents = false;
        }
    }
}
