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
    if (mMouseClickBuffer.getNumEvents() > 0)
    {
        transformMidiBuffer (mMouseClickBuffer);
        mMouseClickBuffer.clear();
    }
    else
    {
        transformMidiBuffer (inMidiBuffer);
    }

    inMidiBuffer.clear();
    inMidiBuffer.swapWith (mTransformedMidiBuffer);
}

//==============================================================================
void MainProcess::handlePlayModeMouseUpOnInput (int inInputNote)
{
    mMouseClickBuffer.addEvent (MidiMessage::noteOff (1, inInputNote, 0.8f), 0);
}

void MainProcess::handlePlayModeMouseDownOnInput (int inInputNote)
{
    mMouseClickBuffer.addEvent (MidiMessage::noteOn (1, inInputNote, 0.8f), 0);
}

//==============================================================================
void MainProcess::transformMidiBuffer (MidiBuffer& inMidiBuffer)
{
    int time;
    MidiMessage message;
    mTransformedMidiBuffer.clear();

    for (MidiBuffer::Iterator index (inMidiBuffer); index.getNextEvent (message, time);)
    {
        if (!mControlsState.isTransposeOff() && mControlsState.isTransposeNote (message.getNoteNumber()))
        {
            if (message.isNoteOn()) { handleTransposeNoteOn (message.getNoteNumber()); }
            if (message.isNoteOff()) { handleTransposeNoteOff (message.getNoteNumber()); }
        }
        else
        {
            if (message.isNoteOn()) { handleNoteOn (message, time); }
            if (message.isNoteOff()) { handleNoteOff (message, time); }
            if (!message.isNoteOnOrOff()) { handleNonNote (message, time); }
        }
    }
}

void MainProcess::handleNoteOn (MidiMessage& inMessage, int inTime)
{
    int inInputNote = inMessage.getNoteNumber();
    int inInputChannel = inMessage.getChannel();
    float inInputVelocity = inMessage.getFloatVelocity();
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    std::map<int, Origin> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.addIfNotAlreadyThere (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        for (int chordNote : mPresetState.getChordNotes (inInputNote))
        {
            noteOnToOutputNotes (inInputNote, inInputChannel, inInputVelocity, inTime, chordNote, currentlyOnOutputNotes);
        }
    }
    else
    {
        noteOnToOutputNotes (inInputNote, inInputChannel, inInputVelocity, inTime, inInputNote, currentlyOnOutputNotes);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNoteOff (MidiMessage& inMessage, int inTime)
{
    int inInputNote = inMessage.getNoteNumber();
    int inInputChannel = inMessage.getChannel();
    float inInputVelocity = inMessage.getFloatVelocity();
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    std::map<int, Origin> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.removeFirstMatchingValue (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        for (int chordNote : mPresetState.getChordNotes (inInputNote))
        {
            noteOffToOutputNotes (inInputNote, inInputChannel, inInputVelocity, inTime, chordNote, currentlyOnOutputNotes);
        }
    }
    else
    {
        noteOffToOutputNotes (inInputNote, inInputChannel, inInputVelocity, inTime, inInputNote, currentlyOnOutputNotes);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNonNote (MidiMessage& inMessage, int inTime)
{
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}

//==============================================================================
void MainProcess::noteOnToOutputNotes (int inInputNote, int inInputChannel, float inInputVelocity, int inTime,
                                       int inOutputNote, std::map<int, Origin>& inCurrentlyOnOutputNotes)
{
    const int triggerCount = mMidiState.getOutputNoteTriggerCount (inOutputNote);

    if (triggerCount == 1)
    {
        const auto& message = MidiMessage::noteOff (inInputChannel, inOutputNote, inInputVelocity);
        mTransformedMidiBuffer.addEvent (message, inTime);

        auto pair = inCurrentlyOnOutputNotes.find (inOutputNote);
        juce::Array<int> triggers = pair->second.triggers;
        triggers.add (inInputNote);
        pair->second.triggers = triggers;
    }

    if (triggerCount == 0)
    {
        juce::Array<int> triggers;
        triggers.add (inInputNote);
        inCurrentlyOnOutputNotes[inOutputNote].triggers = triggers;
    }

    if (triggerCount == 1 || triggerCount == 0)
    {
        const auto& message = MidiMessage::noteOn (inInputChannel, inOutputNote, inInputVelocity);
        mTransformedMidiBuffer.addEvent (message, inTime);
    }
}

void MainProcess::noteOffToOutputNotes (int inInputNote, int inInputChannel, float inInputVelocity, int inTime,
                                        int inOutputNote, std::map<int, Origin>& inCurrentlyOnOutputNotes)
{
    bool containsTrigger = mMidiState.containsOutputNoteTrigger (inOutputNote, inInputNote);
    const int triggerCount = mMidiState.getOutputNoteTriggerCount (inOutputNote);

    if (triggerCount == 2 && containsTrigger)
    {
        auto pair = inCurrentlyOnOutputNotes.find (inOutputNote);
        juce::Array<int> triggers = pair->second.triggers;
        triggers.removeFirstMatchingValue (inInputNote);
        pair->second.triggers = triggers;
    }

    if (triggerCount == 1 && containsTrigger)
    {
        const auto& message = MidiMessage::noteOff (inInputChannel, inOutputNote, inInputVelocity);
        mTransformedMidiBuffer.addEvent (message, inTime);
        inCurrentlyOnOutputNotes.erase (inOutputNote);
    }
}

//==============================================================================
void MainProcess::handleTransposeNoteOn (int inInputNote)
{
    if (inInputNote == mControlsState.getTransposeBase() + 12) { return; }

    if (mControlsState.isTransposeOn() && mMidiState.getCurrentlyOnTransposeNote() == -1)
    {
        mMidiState.setCurrentlyOnTransposeNote (inInputNote);
    }

    else if (mControlsState.isTransposeLocked() && mMidiState.getCurrentlyOnTransposeNote() != inInputNote)
    {
        mMidiState.setCurrentlyOnTransposeNote (inInputNote);
    }

    else if (mControlsState.isTransposeLocked() && mMidiState.getCurrentlyOnTransposeNote() == inInputNote)
    {
        mMidiState.setCurrentlyOnTransposeNote (-1);
    }
}

void MainProcess::handleTransposeNoteOff (int inInputNote)
{
    if (inInputNote == mControlsState.getTransposeBase() + 12) { return; }

    if (mControlsState.isTransposeOn() && mMidiState.getCurrentlyOnTransposeNote() == inInputNote)
    {
        mMidiState.setCurrentlyOnTransposeNote (-1);
    }
}
