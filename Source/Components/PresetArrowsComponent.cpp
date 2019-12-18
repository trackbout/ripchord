#include "PresetArrowsComponent.h"

//==============================================================================
PresetArrowsComponent::PresetArrowsComponent()
{
    mImages.setDrawableButtonImages (mLeftArrowButton, "Prev.svg", "", "PrevON.svg", "");
    mImages.setDrawableButtonImages (mRightArrowButton, "Next.svg", "", "NextON.svg", "");

    mLeftArrowButton.setTriggeredOnMouseDown (true);
    mRightArrowButton.setTriggeredOnMouseDown (true);

    addAndMakeVisible (mLeftArrowButton);
    addAndMakeVisible (mRightArrowButton);
}

PresetArrowsComponent::~PresetArrowsComponent()
{
}

void PresetArrowsComponent::resized()
{
    auto area = getLocalBounds();
    int arrowWidth = area.proportionOfWidth (ARROW_WIDTH / TEXT_INPUT_WIDTH);

    mLeftArrowButton.setBounds (area.removeFromLeft (arrowWidth));
    mRightArrowButton.setBounds (area.removeFromRight (arrowWidth));
}
