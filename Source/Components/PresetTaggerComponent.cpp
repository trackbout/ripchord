#include "PresetTaggerComponent.h"

//==============================================================================
PresetTaggerComponent::PresetTaggerComponent (Preset inPreset)
:   mPreset (inPreset)
{
    mPresetLabel.addMouseListener (this, false);
    mPresetLabel.setText (mPreset.fileName, dontSendNotification);
    mPresetLabel.setColour (Label::textColourId, COLOR_BLACK);
    mPresetLabel.setJustificationType (Justification::centred);

    addAndMakeVisible (mPresetLabel);
}

PresetTaggerComponent::~PresetTaggerComponent()
{
}

//==============================================================================
void PresetTaggerComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_DARK);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void PresetTaggerComponent::resized()
{
    auto area = getLocalBounds();
    mPresetLabel.setFont (Font ((area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO) - 2).boldened());
    mPresetLabel.setBounds (area.reduced (area.getHeight(), 0));
}

void PresetTaggerComponent::mouseDown (const MouseEvent& inEvent)
{
    if (onClick) { onClick (mPreset.indexValue); }
}
