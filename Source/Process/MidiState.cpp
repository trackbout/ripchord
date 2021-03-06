#include "MidiState.h"

//==============================================================================
MidiState::MidiState()
{
}

MidiState::~MidiState()
{
}

//==============================================================================
bool MidiState::isRecording()
{
    return mIsRecording;
}

void MidiState::stopRecording()
{
    mIsRecording = false;
}

//==============================================================================
double MidiState::getCurrentBpm()
{
    return mCurrentBpm;
}

void MidiState::setCurrentChannel (int inChannel)
{
    mCurrentChannel = inChannel;
}

void MidiState::handleTransport (int inNumSamples, double inSampleRate, double inBpm)
{
    int milliseconds = round (1000/(inSampleRate/inNumSamples));

    for (auto& pair : mSampleCounters)
    {
        mSampleCounters[pair.first] = pair.second + milliseconds;
    }

    if (mCurrentBpm != inBpm)
    {
        mCurrentBpm = inBpm;
    }
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
void MidiState::addSampleCounter (int inInputNote)
{
    mSampleCounters[inInputNote] = 0;
}

void MidiState::removeSampleCounter (int inInputNote)
{
    if (mSampleCounters.count (inInputNote) < 1) { return; }
    mSampleCounters.erase (inInputNote);
}

//==============================================================================
void MidiState::addNoteEventToQueue (NoteEvent inNoteEvent, int inIndexInChord, float inDelayDepth, float inDelayVariance)
{
    int delayVarianceMS = inDelayVariance * (rand() % 100 + 1);
    int delayDepthMS = inDelayDepth * MAX_DELAY_DEPTH_MS * inIndexInChord;
    inNoteEvent.delayInMS = delayDepthMS + delayVarianceMS;
    mNoteEventQueue.push (inNoteEvent);
}

void MidiState::removeNoteEventsFromQueue (int inInputNote)
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

//==============================================================================
bool MidiState::timeToSendNextNoteEvent()
{
    if (mNoteEventQueue.size() == 0) { return false; }

    NoteEvent nextNoteEvent = mNoteEventQueue.front();
    if (mSampleCounters.count (nextNoteEvent.inputNote) == 0) { return false; }

    int elapsedMS = mSampleCounters.at (nextNoteEvent.inputNote);
    if (nextNoteEvent.delayInMS > elapsedMS) { return false; }

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
void MidiState::setActiveTransposeNoteIfAllowed (const int inputNote)
{
    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kActiveTransposeNoteAllowed;
    message->messageVar1 = inputNote;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void MidiState::clearRecordedSequence()
{
    mRecordedSequence.clear();
}

bool MidiState::isRecordedSequenceEmpty()
{
    return mRecordedSequence.getNumEvents() == 0;
}

MidiMessageSequence MidiState::getRecordedSequence()
{
    return mRecordedSequence;
}

void MidiState::addToRecordedSequence (MidiMessage inMidiMessage)
{
    if (!mIsRecording)
    {
        mIsRecording = true;
        mStartTime = Time::getMillisecondCounterHiRes();

        DataMessage* message = new DataMessage();
        message->messageCode = MessageCode::kIsRecording;
        sendMessage (message, ListenerType::kAsync);
    }

    float const msPerTick = (MS_PER_MINUTE / mCurrentBpm) / TICKS_PER_QUARTER_NOTE;
    double timeStampInMs = Time::getMillisecondCounterHiRes() - mStartTime;
    inMidiMessage.setTimeStamp (timeStampInMs / msPerTick);
    mRecordedSequence.addEvent (inMidiMessage);
}

//==============================================================================
void MidiState::scrubMidiState (MidiBuffer& inMidiBuffer)
{
    if (mCurrentlyOnInputNotes.size() > 0)
    {
        return;
    }

    if (mSampleCounters.size() > 0)
    {
        mSampleCounters.clear();
    }

    if (mNoteEventQueue.size() > 0)
    {
        std::queue<NoteEvent> emptyQueue;
        std::swap (mNoteEventQueue, emptyQueue);
    }

    if (mCurrentlyOnOutputNotes.size() > 0)
    {
        for (const auto& pair : mCurrentlyOnOutputNotes)
        {
            inMidiBuffer.addEvent (MidiMessage::noteOff (mCurrentChannel, pair.first), 0);
        }

        mCurrentlyOnOutputNotes.clear();

        DataMessage* message = new DataMessage();
        message->messageCode = MessageCode::kClearStuckNotes;
        sendMessage (message, ListenerType::kAsync);
    }
}
