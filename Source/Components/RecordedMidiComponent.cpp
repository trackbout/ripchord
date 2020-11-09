#include "RecordedMidiComponent.h"

//==============================================================================
RecordedMidiComponent::RecordedMidiComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess)
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
    MidiMessageSequence sequence;
    sequence.addEvent (MidiMessage::noteOn (1, 54, 0.8f), 0.0f);
    sequence.addEvent (MidiMessage::noteOn (1, 59, 0.8f), 0.0f);
    sequence.addEvent (MidiMessage::noteOn (1, 62, 0.8f), 0.0f);
    sequence.addEvent (MidiMessage::noteOff (1, 54), TICKS_PER_QUARTER_NOTE * 4.0f);
    sequence.addEvent (MidiMessage::noteOff (1, 59), TICKS_PER_QUARTER_NOTE * 4.0f);
    sequence.addEvent (MidiMessage::noteOff (1, 62), TICKS_PER_QUARTER_NOTE * 4.0f);

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
