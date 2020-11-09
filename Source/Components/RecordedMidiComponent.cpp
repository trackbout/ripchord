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
    if (mMidiState.isRecordedSequenceEmpty()) { return; }

    MidiMessageSequence sequence = mMidiState.getRecordedSequence();

    MidiFile midiFile;
    midiFile.setTicksPerQuarterNote (TICKS_PER_QUARTER_NOTE);
    midiFile.addTrack (sequence);

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
