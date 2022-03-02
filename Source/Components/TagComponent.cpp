#include "TagComponent.h"

//==============================================================================
TagComponent::TagComponent (String inName, String inType, bool inIsSelected)
:   mName (inName),
    mType (inType),
    mIsSelected (inIsSelected),
    mDeleteComponent ("tag")
{
    mTagLabel.addMouseListener (this, false);
    mTagLabel.setText (mName, dontSendNotification);
    mTagLabel.setColour (Label::textColourId, COLOR_BLACK);
    mTagLabel.setJustificationType (Justification::centred);

    addAndMakeVisible (mTagLabel);
    addAndMakeVisible (mTrashButton);

    if (mType == "browser")
    {
        mImages.setDrawableButtonImages (mTrashButton, "Trash.svg");
        mTrashButton.setTriggeredOnMouseDown (true);
        mTrashButton.onClick = [this]() { mDeleteComponent.setVisible (true); };
        mDeleteComponent.onClick = [this]() { if (onDelete) { onDelete (mName); } };
        addChildComponent (mDeleteComponent);
    }
}

TagComponent::~TagComponent()
{
}

//==============================================================================
void TagComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (mIsSelected ? COLOR_PURPLE : COLOR_GREY);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void TagComponent::resized()
{
    auto area = getLocalBounds();
    mTagLabel.setFont (Font ((area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO) + 1).boldened());

    if (mType == "bar")
    {
        mTagLabel.setBounds (area.reduced ((area.getHeight() * 0.1f), 0));
    }

    if (mType == "browser")
    {
        mDeleteComponent.setBounds (area);
        mTagLabel.setBounds (area.reduced ((area.getHeight() * 0.7f), 0));

        juce::Rectangle<float> trashAreaProportion (TRASH_TAG_X / PRESET_WIDTH, TRASH_TAG_Y / ITEM_HEIGHT,
                                                    TRASH_WIDTH / PRESET_WIDTH, TRASH_HEIGHT / ITEM_HEIGHT);

        mTrashButton.setBounds (area.getProportion (trashAreaProportion));
    }
}

//==============================================================================
void TagComponent::mouseDown (const MouseEvent& inEvent)
{

}
