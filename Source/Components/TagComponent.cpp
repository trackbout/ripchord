#include "TagComponent.h"

//==============================================================================
TagComponent::TagComponent (String inName)
:   mName (inName),
    mDeleteComponent ("tag")
{
    mTagLabel.addMouseListener (this, false);
    mTagLabel.setText (mName, dontSendNotification);
    mTagLabel.setColour (Label::textColourId, COLOR_BLACK);
    mTagLabel.setJustificationType (Justification::centred);

    mImages.setDrawableButtonImages (mTrashButton, "Trash.svg");
    mTrashButton.setTriggeredOnMouseDown (true);
    mTrashButton.onClick = [this]() { mDeleteComponent.setVisible (true); };

    mDeleteComponent.onClick = [this]() { if (onDelete) { onDelete (mName); } };

    addAndMakeVisible (mTagLabel);
    addAndMakeVisible (mTrashButton);
    addChildComponent (mDeleteComponent);
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
    mDeleteComponent.setBounds (area);

    juce::Rectangle<float> trashAreaProportion (TRASH_TAG_X / PRESET_WIDTH, TRASH_TAG_Y / ITEM_HEIGHT,
                                                TRASH_WIDTH / PRESET_WIDTH, TRASH_HEIGHT / ITEM_HEIGHT);

    mTrashButton.setBounds (area.getProportion (trashAreaProportion));

    mTagLabel.setFont (Font ((area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO) - 2).boldened());
    mTagLabel.setBounds (area.reduced (area.getHeight(), 0));
}

void TagComponent::mouseDown (const MouseEvent& inEvent)
{

}
