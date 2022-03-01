#include "DeleteComponent.h"

//==============================================================================
DeleteComponent::DeleteComponent(String inType)
:   mType (inType)
{
    mImages.setDrawableButtonImages (mCancelButton, "Cancel.svg");
    mImages.setDrawableButtonImages (mDeleteButton, "Delete.svg");

    mCancelButton.setTriggeredOnMouseDown (true);
    mDeleteButton.setTriggeredOnMouseDown (true);

    mCancelButton.onClick = [this]() { setVisible (false); };
    mDeleteButton.onClick = [this]() { if (onClick) { onClick(); } };

    addAndMakeVisible (mCancelButton);
    addAndMakeVisible (mDeleteButton);
}

DeleteComponent::~DeleteComponent()
{
}

void DeleteComponent::paint(Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void DeleteComponent::resized()
{
    auto presetArea = getLocalBounds();
    
    const float CANCEL_X = mType == "preset" ? CANCEL_PRESET_X : CANCEL_TAG_X;
    const float DELETE_X = mType == "preset" ? DELETE_PRESET_X : DELETE_TAG_X;
    const float PARENT_WIDTH = mType == "preset" ? PRESET_WIDTH : BROWSER_TAG_WIDTH;

    juce::Rectangle<float> cancelProportion (CANCEL_X / PARENT_WIDTH, CANCEL_Y / ITEM_HEIGHT,
                                             CANCEL_WIDTH / PARENT_WIDTH, CANCEL_HEIGHT / ITEM_HEIGHT);

    juce::Rectangle<float> deleteProportion (DELETE_X / PARENT_WIDTH, DELETE_Y / ITEM_HEIGHT,
                                             DELETE_WIDTH / PARENT_WIDTH, DELETE_HEIGHT / ITEM_HEIGHT);

    mCancelButton.setBounds (presetArea.getProportion (cancelProportion));
    mDeleteButton.setBounds (presetArea.getProportion (deleteProportion));
}
