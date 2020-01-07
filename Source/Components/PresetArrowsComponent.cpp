#include "PresetArrowsComponent.h"

//==============================================================================
PresetArrowsComponent::PresetArrowsComponent()
{
    mPresetNameLabel.setJustificationType (Justification::centred);

    mImages.setDrawableButtonImages (mLeftArrowButton, "Prev.svg", "", "PrevON.svg", "");
    mImages.setDrawableButtonImages (mRightArrowButton, "Next.svg", "", "NextON.svg", "");

    mLeftArrowButton.setTriggeredOnMouseDown (true);
    mRightArrowButton.setTriggeredOnMouseDown (true);

    mLeftArrowButton.onClick = [this]() { if (onLeftArrowClick) onLeftArrowClick(); };
    mRightArrowButton.onClick = [this]() { if (onRightArrowClick) onRightArrowClick(); };

    addAndMakeVisible (mPresetNameLabel);
    addAndMakeVisible (mLeftArrowButton);
    addAndMakeVisible (mRightArrowButton);
}

PresetArrowsComponent::~PresetArrowsComponent()
{
}

//==============================================================================
void PresetArrowsComponent::resized()
{
    auto area = getLocalBounds();
    int arrowWidth = area.proportionOfWidth (ARROW_WIDTH / TEXT_INPUT_WIDTH);

    mLeftArrowButton.setBounds (area.removeFromLeft (arrowWidth));
    mRightArrowButton.setBounds (area.removeFromRight (arrowWidth));

    mPresetNameLabel.setBounds (area);
    mPresetNameLabel.setFont (Font (area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO).boldened());
}

void PresetArrowsComponent::updateTextLabel (String inPresetName)
{
    mPresetNameLabel.setText (inPresetName, dontSendNotification);
}
