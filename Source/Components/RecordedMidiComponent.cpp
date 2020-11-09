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
    DBG ("woot");
}

//==============================================================================
void RecordedMidiComponent::setButtonImage (const String inImagePath)
{
    mImages.setDrawableButtonImages (mRecordedButton, inImagePath);
}
