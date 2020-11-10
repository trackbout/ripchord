#include "RecordedMidiComponent.h"

//==============================================================================
RecordedMidiComponent::RecordedMidiComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mMidiState (mMainProcess.getMidiState())
{
    mImages.setDrawableButtonImages (mRecordedButton, "Recorded.svg");
    mRecordedButton.setInterceptsMouseClicks (false, false);
    addAndMakeVisible (mRecordedButton);
}

RecordedMidiComponent::~RecordedMidiComponent()
{
}

//==============================================================================
void RecordedMidiComponent::resized()
{
    mRecordedButton.setBounds (getLocalBounds());
}

//==============================================================================
void RecordedMidiComponent::mouseDown (const MouseEvent& inEvent)
{
    if (mMidiState.isRecording() || mMidiState.isRecordedSequenceEmpty()) { return; }

    int microsPerQuarterNote = (MS_PER_MINUTE / mMidiState.getCurrentBpm()) * 1000.f;
    MidiMessage tempoEvent = MidiMessage::tempoMetaEvent (microsPerQuarterNote);
    tempoEvent.setTimeStamp (0);

    MidiMessageSequence recordedSequence = mMidiState.getRecordedSequence();
    recordedSequence.addEvent (tempoEvent);
    recordedSequence.updateMatchedPairs();
    recordedSequence.sort();

    MidiFile midiFile;
    midiFile.setTicksPerQuarterNote (TICKS_PER_QUARTER_NOTE);
    midiFile.addTrack (recordedSequence);

    File temp = COMPANY_FOLDER.getChildFile ("Ripchord.mid");

    if (auto stream = std::unique_ptr<FileOutputStream> (temp.createOutputStream()))
    {
        midiFile.writeTo (*stream, 0);
        performExternalDragDropOfFiles ({ temp.getFullPathName() }, false, nullptr, [=](void){ temp.deleteFile(); });
    }
}

//==============================================================================
void RecordedMidiComponent::setButtonImage (const String inImagePath)
{
    mImages.setDrawableButtonImages (mRecordedButton, inImagePath);
}
