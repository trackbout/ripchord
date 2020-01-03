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
    std::map<int, int> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.addIfNotAlreadyThere (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        for (const int chordNote : mPresetState.getChordNotes (inInputNote))
        {
            if (mMidiState.containsCurrentlyOnOutputNote (chordNote))
            {
                const auto& message = MidiMessage::noteOff (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                currentlyOnOutputNotes.erase (chordNote);
            }

            const auto& message = MidiMessage::noteOn (inInputChannel, chordNote, inInputVelocity);
            mTransformedMidiBuffer.addEvent (message, inTime);
            currentlyOnOutputNotes[chordNote] = inInputNote;
        }
    }

    else
    {
        if (mMidiState.containsCurrentlyOnOutputNote (inInputNote))
        {
            const auto& message = MidiMessage::noteOff (inInputChannel, inInputNote, inInputVelocity);
            mTransformedMidiBuffer.addEvent (message, inTime);
            currentlyOnOutputNotes.erase (inInputNote);
        }

        mTransformedMidiBuffer.addEvent (inMessage, inTime);
        currentlyOnOutputNotes[inInputNote] = inInputNote;
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
    std::map<int, int> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.removeFirstMatchingValue (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        for (const int chordNote : mPresetState.getChordNotes (inInputNote))
        {
            if (mMidiState.wasOutputNoteTriggeredByInputNote (chordNote, inInputNote))
            {
                const auto& message = MidiMessage::noteOff (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                currentlyOnOutputNotes.erase (chordNote);
            }
        }
    }

    else if (mMidiState.wasOutputNoteTriggeredByInputNote (inInputNote, inInputNote))
    {
        mTransformedMidiBuffer.addEvent (inMessage, inTime);
        currentlyOnOutputNotes.erase (inInputNote);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNonNote (MidiMessage inMessage, int inTime)
{
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}
