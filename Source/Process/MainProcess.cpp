#include "MainProcess.h"

//==============================================================================
MainProcess::MainProcess()
{
}

MainProcess::~MainProcess()
{
}

//==============================================================================
void MainProcess::handleMidiBuffer (MidiBuffer& inMidiBuffer, int inNumberOfSamples)
{
    transformMidiBuffer (inMidiBuffer);
    inMidiBuffer.clear();
    inMidiBuffer.swapWith (mTransformedMidiBuffer);
}

//==============================================================================
void MainProcess::transformMidiBuffer (MidiBuffer& inMidiBuffer)
{
    int time;
    MidiMessage message;
    mTransformedMidiBuffer.clear();

    for (MidiBuffer::Iterator index (inMidiBuffer); index.getNextEvent(message, time);)
    {
        if (message.isNoteOn()) { handleNoteOn (message, time); }

        if (message.isNoteOff()) { handleNoteOff (message, time); }

        if (!message.isNoteOnOrOff()) { handleNonNote (message, time); }
    }
}

void MainProcess::handleNoteOn (MidiMessage inMessage, int inTime)
{
    const int inInputNote = inMessage.getNoteNumber();
    const int inInputChannel = inMessage.getChannel();
    const float inInputVelocity = inMessage.getFloatVelocity();
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    std::map<int, juce::Array<int>> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.addIfNotAlreadyThere (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        for (const int chordNote : mPresetState.getChordNotes (inInputNote))
        {
            const int triggerCount = mMidiState.getOutputNoteTriggerCount (chordNote, inInputNote);

            if (triggerCount < 2 && mMidiState.containsCurrentlyOnOutputNote (chordNote))
            {
                const auto& message = MidiMessage::noteOff (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
            }

            if (triggerCount < 2)
            {
                const auto& message = MidiMessage::noteOn (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                mMidiState.addTrigger (currentlyOnOutputNotes, chordNote, inInputNote);
            }
        }
    }

    else
    {
        const int triggerCount = mMidiState.getOutputNoteTriggerCount (inInputNote, inInputNote);

        if (triggerCount < 2 && mMidiState.containsCurrentlyOnOutputNote (inInputNote))
        {
            const auto& message = MidiMessage::noteOff (inInputChannel, inInputNote, inInputVelocity);
            mTransformedMidiBuffer.addEvent (message, inTime);
        }

        if (triggerCount < 2)
        {
            mTransformedMidiBuffer.addEvent (inMessage, inTime);
            mMidiState.addTrigger (currentlyOnOutputNotes, inInputNote, inInputNote);
        }
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNoteOff (MidiMessage inMessage, int inTime)
{
    const int inInputNote = inMessage.getNoteNumber();
    const int inInputChannel = inMessage.getChannel();
    const float inInputVelocity = inMessage.getFloatVelocity();
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    std::map<int, juce::Array<int>> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.removeFirstMatchingValue (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        for (const int chordNote : mPresetState.getChordNotes (inInputNote))
        {
            const int triggerCount = mMidiState.getOutputNoteTriggerCount (chordNote, inInputNote);
            bool containsTrigger = mMidiState.containsOutputNoteTrigger (chordNote, inInputNote);

            if (triggerCount == 2 && containsTrigger)
            {
                mMidiState.removeTrigger (currentlyOnOutputNotes, chordNote, inInputNote);
            }

            if (triggerCount == 1 && containsTrigger)
            {
                const auto& message = MidiMessage::noteOff (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                currentlyOnOutputNotes.erase (inInputNote);
            }
        }
    }

    else
    {
        const int triggerCount = mMidiState.getOutputNoteTriggerCount (inInputNote, inInputNote);
        bool containsTrigger = mMidiState.containsOutputNoteTrigger (inInputNote, inInputNote);

        if (triggerCount == 2 && containsTrigger)
        {
            mMidiState.removeTrigger (currentlyOnOutputNotes, inInputNote, inInputNote);
        }

        if (triggerCount == 1 && containsTrigger)
        {
            mTransformedMidiBuffer.addEvent (inMessage, inTime);
            currentlyOnOutputNotes.erase (inInputNote);
        }
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNonNote (MidiMessage inMessage, int inTime)
{
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}
