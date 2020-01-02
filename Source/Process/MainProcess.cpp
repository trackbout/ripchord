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
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}

void MainProcess::handleNoteOff (MidiMessage inMessage, int inTime)
{
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}

void MainProcess::handleNonNote (MidiMessage inMessage, int inTime)
{
    mTransformedMidiBuffer.addEvent (inMessage, inTime);
}
