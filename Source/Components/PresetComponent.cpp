#include "PresetComponent.h"

//==============================================================================
PresetComponent::PresetComponent()
{
    mPresetLabel.setColour (Label::textColourId, COLOR_GREY_DARK);
    mPresetLabel.setJustificationType (Justification::centred);

    mImages.setDrawableButtonImages (mTrashButton, "Trash.svg");
    mImages.setDrawableButtonImages (mStarButton, "Star.svg", "", "", "", "StarON.svg", "", "", "");

    mTrashButton.setTriggeredOnMouseDown (true);
    mStarButton.setTriggeredOnMouseDown (true);

    addAndMakeVisible (mPresetLabel);
    addAndMakeVisible (mStarButton);
    addAndMakeVisible (mTrashButton);
    addChildComponent (mPresetDeleteComponent);
}

PresetComponent::~PresetComponent()
{
}

//==============================================================================
void PresetComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_WHITE);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void PresetComponent::resized()
{
    auto area = getLocalBounds();
    mPresetDeleteComponent.setBounds (area);

    juce::Rectangle<float> starAreaProportion (STAR_X / PRESET_WIDTH, STAR_Y / ITEM_HEIGHT,
                                               STAR_WIDTH / PRESET_WIDTH, STAR_HEIGHT / ITEM_HEIGHT);

    juce::Rectangle<float> trashAreaProportion (TRASH_X / PRESET_WIDTH, TRASH_Y / ITEM_HEIGHT,
                                                TRASH_WIDTH / PRESET_WIDTH, TRASH_HEIGHT / ITEM_HEIGHT);

    mStarButton.setBounds (area.getProportion (starAreaProportion));
    mTrashButton.setBounds (area.getProportion (trashAreaProportion));

    mPresetLabel.setFont (area.getHeight() * (TEXT_INPUT_FONT_HEIGHT_RATIO - 0.1f));
    mPresetLabel.setBounds (area.reduced (area.getHeight(), 0));
}
