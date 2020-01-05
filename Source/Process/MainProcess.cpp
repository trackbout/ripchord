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

            if (triggerCount == 1)
            {
                const auto& message = MidiMessage::noteOff (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);

                auto pair = currentlyOnOutputNotes.find (chordNote);
                juce::Array<int> triggers = pair->second;
                triggers.add (inInputNote);
                pair->second = triggers;
            }

            if (triggerCount == 0)
            {
                juce::Array<int> triggers;
                triggers.add (inInputNote);
                currentlyOnOutputNotes[chordNote] = triggers;
            }

            if (triggerCount == 1 || triggerCount == 0)
            {
                const auto& message = MidiMessage::noteOn (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
            }
        }
    }

    else
    {
        const int triggerCount = mMidiState.getOutputNoteTriggerCount (inInputNote, inInputNote);

        if (triggerCount == 1)
        {
            const auto& message = MidiMessage::noteOff (inInputChannel, inInputNote, inInputVelocity);
            mTransformedMidiBuffer.addEvent (message, inTime);

            auto pair = currentlyOnOutputNotes.find (inInputNote);
            juce::Array<int> triggers = pair->second;
            triggers.add (inInputNote);
            pair->second = triggers;
        }

        if (triggerCount == 0)
        {
            juce::Array<int> triggers;
            triggers.add (inInputNote);
            currentlyOnOutputNotes[inInputNote] = triggers;
        }

        if (triggerCount == 1 || triggerCount == 0)
        {
            mTransformedMidiBuffer.addEvent (inMessage, inTime);
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
            bool containsTrigger = mMidiState.containsOutputNoteTrigger (chordNote, inInputNote);
            const int triggerCount = mMidiState.getOutputNoteTriggerCount (chordNote, inInputNote);

            if (triggerCount == 2 && containsTrigger)
            {
                auto pair = currentlyOnOutputNotes.find (chordNote);
                juce::Array<int> triggers = pair->second;
                triggers.removeFirstMatchingValue (inInputNote);
                pair->second = triggers;
            }

            if (triggerCount == 1 && containsTrigger)
            {
                const auto& message = MidiMessage::noteOff (inInputChannel, chordNote, inInputVelocity);
                mTransformedMidiBuffer.addEvent (message, inTime);
                currentlyOnOutputNotes.erase (chordNote);
            }
        }
    }

    else
    {
        bool containsTrigger = mMidiState.containsOutputNoteTrigger (inInputNote, inInputNote);
        const int triggerCount = mMidiState.getOutputNoteTriggerCount (inInputNote, inInputNote);

        if (triggerCount == 2 && containsTrigger)
        {
            auto pair = currentlyOnOutputNotes.find (inInputNote);
            juce::Array<int> triggers = pair->second;
            triggers.removeFirstMatchingValue (inInputNote);
            pair->second = triggers;
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
