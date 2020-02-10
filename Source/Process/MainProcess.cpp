#include "MainProcess.h"

//==============================================================================
MainProcess::MainProcess()
{
}

MainProcess::~MainProcess()
{
}

//==============================================================================
void MainProcess::handleMidiBuffer (MidiBuffer& inMidiBuffer)
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

    handleNoteEventQueu();

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
    int sampleNumber;
    MidiMessage message;
    mTransformedMidiBuffer.clear();

    for (MidiBuffer::Iterator index (inMidiBuffer); index.getNextEvent (message, sampleNumber);)
    {
        if (mGlobalState.isPlayMode() &&
            mControlsState.isTransposeOn() &&
            mControlsState.isTransposeNote (message.getNoteNumber()))
        {
            if (message.isNoteOn()) { handleActiveTransposeNote (message.getNoteNumber()); }
        }
        else
        {
            if (message.isNoteOn()) { handleNoteOn (message, sampleNumber); }
            if (message.isNoteOff()) { handleNoteOff (message, sampleNumber); }
            if (!message.isNoteOnOrOff()) { handleNonNote (message, sampleNumber); }
        }
    }
}

void MainProcess::handleNoteOn (MidiMessage& inMessage, int inSampleNumber)
{
    bool isNoteOn = true;
    int inChannel = inMessage.getChannel();
    int inInputNote = inMessage.getNoteNumber();
    float inVelocity = inMessage.getFloatVelocity();
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    std::map<int, Origin> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.addIfNotAlreadyThere (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        juce::Array<int> chordNotes = mPresetState.getChordNotes (inInputNote);

        for (int index = 0; index < chordNotes.size(); index++)
        {
            float delayDepth = mControlsState.getDelayDepth();
            float delayVariance = mControlsState.getDelayVariance();
            int activeTransposeNote = mControlsState.getActiveTransposeNote();
            int transposedNote = mControlsState.getTransposedNote (chordNotes[index], activeTransposeNote);
            int chordNote = mGlobalState.isPlayMode() ? transposedNote : chordNotes[index];
            NoteEvent noteEvent { inChannel, inSampleNumber, inVelocity, inInputNote, chordNote, isNoteOn };

            if (index == 0 || (delayDepth < MIN_DELAY_DEPTH && delayVariance < MIN_DELAY_VARIANCE))
            {
                sendOutputNoteOn (noteEvent, currentlyOnOutputNotes);
            }
            else
            {
                mMidiState.addNoteEventToQueu (noteEvent, index, delayDepth, delayVariance);
            }
        }
    }
    else
    {
        NoteEvent noteEvent { inChannel, inSampleNumber, inVelocity, inInputNote, inInputNote, isNoteOn };
        sendOutputNoteOn (noteEvent, currentlyOnOutputNotes);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNoteOff (MidiMessage& inMessage, int inSampleNumber)
{
    bool isNoteOn = false;
    int inChannel = inMessage.getChannel();
    int inInputNote = inMessage.getNoteNumber();
    float inVelocity = inMessage.getFloatVelocity();
    juce::Array<int> currentlyOnInputNotes = mMidiState.getCurrentlyOnInputNotes();
    std::map<int, Origin> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();

    currentlyOnInputNotes.removeFirstMatchingValue (inInputNote);

    if (mPresetState.containsChord (inInputNote))
    {
        juce::Array<int> chordNotes = mPresetState.getChordNotes (inInputNote);

        for (int index = 0; index < chordNotes.size(); index++)
        {
            float delayDepth = mControlsState.getDelayDepth();
            float delayVariance = mControlsState.getDelayVariance();
            int activeTransposeNote = mControlsState.getActiveTransposeNote();
            int transposedNote = mControlsState.getTransposedNote (chordNotes[index], activeTransposeNote);
            int chordNote = mGlobalState.isPlayMode() ? transposedNote : chordNotes[index];
            NoteEvent noteEvent { inChannel, inSampleNumber, inVelocity, inInputNote, chordNote, isNoteOn };

            if (index == 0 || (delayDepth < MIN_DELAY_DEPTH && delayVariance < MIN_DELAY_VARIANCE))
            {
                sendOutputNoteOff (noteEvent, currentlyOnOutputNotes);
            }
            else
            {
                mMidiState.addNoteEventToQueu (noteEvent, index, delayDepth, delayVariance);
            }
        }
    }
    else
    {
        NoteEvent noteEvent { inChannel, inSampleNumber, inVelocity, inInputNote, inInputNote, isNoteOn };
        sendOutputNoteOff (noteEvent, currentlyOnOutputNotes);
    }

    mMidiState.setCurrentlyOnInputNotes (currentlyOnInputNotes);
    mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
}

void MainProcess::handleNonNote (MidiMessage& inMessage, int inSampleNumber)
{
    mTransformedMidiBuffer.addEvent (inMessage, inSampleNumber);
}

//==============================================================================
void MainProcess::sendOutputNoteOn (NoteEvent inNoteEvent, std::map<int, Origin>& inCurrentlyOnOutputNotes)
{
    const int triggerCount = mMidiState.getOutputNoteTriggerCount (inNoteEvent.outputNote);

    if (triggerCount == 1)
    {
        const auto& message = MidiMessage::noteOff (inNoteEvent.channel, inNoteEvent.outputNote, inNoteEvent.velocity);
        mTransformedMidiBuffer.addEvent (message, inNoteEvent.sampleNumber);

        auto pair = inCurrentlyOnOutputNotes.find (inNoteEvent.outputNote);
        juce::Array<int> triggers = pair->second.triggers;
        triggers.add (inNoteEvent.inputNote);
        pair->second.triggers = triggers;
    }

    if (triggerCount == 0)
    {
        juce::Array<int> triggers;
        triggers.add (inNoteEvent.inputNote);
        inCurrentlyOnOutputNotes[inNoteEvent.outputNote].triggers = triggers;
    }

    if (triggerCount == 1 || triggerCount == 0)
    {
        const auto& message = MidiMessage::noteOn (inNoteEvent.channel, inNoteEvent.outputNote, inNoteEvent.velocity);
        mTransformedMidiBuffer.addEvent (message, inNoteEvent.sampleNumber);
    }
}

void MainProcess::sendOutputNoteOff (NoteEvent inNoteEvent, std::map<int, Origin>& inCurrentlyOnOutputNotes)
{
    bool containsTrigger = mMidiState.containsOutputNoteTrigger (inNoteEvent.outputNote, inNoteEvent.inputNote);
    const int triggerCount = mMidiState.getOutputNoteTriggerCount (inNoteEvent.outputNote);

    if (triggerCount == 2 && containsTrigger)
    {
        auto pair = inCurrentlyOnOutputNotes.find (inNoteEvent.outputNote);
        juce::Array<int> triggers = pair->second.triggers;
        triggers.removeFirstMatchingValue (inNoteEvent.inputNote);
        pair->second.triggers = triggers;
    }

    if (triggerCount == 1 && containsTrigger)
    {
        const auto& message = MidiMessage::noteOff (inNoteEvent.channel, inNoteEvent.outputNote, inNoteEvent.velocity);
        mTransformedMidiBuffer.addEvent (message, inNoteEvent.sampleNumber);
        inCurrentlyOnOutputNotes.erase (inNoteEvent.outputNote);
    }
}

//==============================================================================
void MainProcess::handleNoteEventQueu()
{
    for (NoteEvent& noteEvent : mMidiState.getNoteEventsToSend())
    {
        std::map<int, Origin> currentlyOnOutputNotes = mMidiState.getCurrentlyOnOutputNotes();
        if (noteEvent.isNoteOn) { sendOutputNoteOn (noteEvent, currentlyOnOutputNotes); }
        if (!noteEvent.isNoteOn) { sendOutputNoteOff (noteEvent, currentlyOnOutputNotes); }
        mMidiState.setCurrentlyOnOutputNotes (currentlyOnOutputNotes);
    }
}

//==============================================================================
void MainProcess::handleActiveTransposeNote (int inInputNote)
{
    if (inInputNote == mControlsState.getTransposeBase() + 12) { return; }
    if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }

    else if (mControlsState.getActiveTransposeNote() != inInputNote)
    {
        mMidiState.setActiveTransposeNoteIfAllowed (inInputNote);
    }

    else if (mControlsState.getActiveTransposeNote() == inInputNote)
    {
        mMidiState.setActiveTransposeNoteIfAllowed (-1);
    }
}

//==============================================================================
XmlElement* MainProcess::exportSessionXml()
{
    XmlElement* sessionXml = new XmlElement ("Session");
    sessionXml->addChildElement (mControlsState.exportControlsStateXml());
    sessionXml->addChildElement (mPresetState.exportPresetStateXml());
    return sessionXml;
}

void MainProcess::importSessionXml (XmlElement* inSessionXml)
{
    if (inSessionXml->getTagName() != "Session") { return; }

    XmlElement* controlsStateXml = inSessionXml->getChildByName("ControlsState");
    XmlElement* presetStateXml = inSessionXml->getChildByName("PresetState");

    mControlsState.importControlsStateXml (controlsStateXml);
    mPresetState.importPresetStateXml (presetStateXml);
}
