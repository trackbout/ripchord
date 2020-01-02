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
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    juce::Array<int> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    const int inputNote = inMessage.getNoteNumber();
    currentlyOnInputNotes.addIfNotAlreadyThere (inputNote);

    if (mPresetState.containsChord (inputNote))
    {
        const int inputChannel = inMessage.getChannel();
        const float inputVelocity = inMessage.getFloatVelocity();

        for (const int chordNote : mPresetState.getChordNotes (inputNote))
        {
            if (!currentlyOnOutputNotes.contains (chordNote))
            {
                const auto& message = MidiMessage::noteOn (inputChannel, chordNote, inputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                currentlyOnOutputNotes.add (chordNote);
            }
        }
    }

    else if (!currentlyOnOutputNotes.contains (inputNote))
    {
        mTransformedMidiBuffer.addEvent (inMessage, inTime);
        currentlyOnOutputNotes.add (inputNote);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNoteOff (MidiMessage inMessage, int inTime)
{
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    juce::Array<int> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    const int inputNote = inMessage.getNoteNumber();
    currentlyOnInputNotes.removeFirstMatchingValue (inputNote);

    if (mPresetState.containsChord (inputNote))
    {
        const int inputChannel = inMessage.getChannel();
        const float inputVelocity = inMessage.getFloatVelocity();

        for (const int chordNote : mPresetState.getChordNotes (inputNote))
        {
            if (currentlyOnOutputNotes.contains (chordNote))
            {
                const auto& message = MidiMessage::noteOff (inputChannel, chordNote, inputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                currentlyOnOutputNotes.removeFirstMatchingValue (chordNote);
            }
        }
    }

    else if (currentlyOnOutputNotes.contains (inputNote))
    {
        mTransformedMidiBuffer.addEvent (inMessage, inTime);
        currentlyOnOutputNotes.removeFirstMatchingValue (inputNote);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNonNote (MidiMessage inMessage, int inTime)
{
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}
