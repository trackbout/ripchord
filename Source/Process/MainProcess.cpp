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
    inMidiBuffer.clear();
    inMidiBuffer.swapWith (mMidiBuffer);
}
