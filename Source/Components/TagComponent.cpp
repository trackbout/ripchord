#include "TagComponent.h"

//==============================================================================
TagComponent::TagComponent (String inName)
:   mName (inName)
{
    mTagLabel.addMouseListener (this, false);
    mTagLabel.setText (mName, dontSendNotification);
    mTagLabel.setColour (Label::textColourId, COLOR_BLACK);
    mTagLabel.setJustificationType (Justification::centred);

    addAndMakeVisible (mTagLabel);
}

TagComponent::~TagComponent()
{
}

//==============================================================================
void TagComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void TagComponent::resized()
{
    auto area = getLocalBounds();
    mTagLabel.setFont (Font ((area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO) - 2).boldened());
    mTagLabel.setBounds (area.reduced (area.getHeight(), 0));
}

void TagComponent::mouseDown (const MouseEvent& inEvent)
{

}
