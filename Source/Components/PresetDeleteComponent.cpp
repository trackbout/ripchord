#include "PresetDeleteComponent.h"

//==============================================================================
PresetDeleteComponent::PresetDeleteComponent()
{
    mImages.setDrawableButtonImages (mCancelButton, "Cancel.svg");
    mImages.setDrawableButtonImages (mDeleteButton, "Delete.svg");

    mCancelButton.setTriggeredOnMouseDown (true);
    mDeleteButton.setTriggeredOnMouseDown (true);

    addAndMakeVisible (mCancelButton);
    addAndMakeVisible (mDeleteButton);
}

PresetDeleteComponent::~PresetDeleteComponent()
{
}

void PresetDeleteComponent::paint(Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_WHITE);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void PresetDeleteComponent::resized()
{
    auto presetArea = getLocalBounds();

    juce::Rectangle<float> cancelProportion (CANCEL_X / PRESET_WIDTH, CANCEL_Y / ITEM_HEIGHT,
                                             CANCEL_WIDTH / PRESET_WIDTH, CANCEL_HEIGHT / ITEM_HEIGHT);

    juce::Rectangle<float> deleteProportion (DELETE_X / PRESET_WIDTH, DELETE_Y / ITEM_HEIGHT,
                                             DELETE_WIDTH / PRESET_WIDTH, DELETE_HEIGHT / ITEM_HEIGHT);

    mCancelButton.setBounds (presetArea.getProportion (cancelProportion));
    mDeleteButton.setBounds (presetArea.getProportion (deleteProportion));
}
