#include "PresetTaggerComponent.h"

//==============================================================================
PresetTaggerComponent::PresetTaggerComponent (Preset inPreset, bool inIsInAssignableTag)
:   mPreset (inPreset),
    mIsInAssignableTag (inIsInAssignableTag)
{
    mPresetLabel.addMouseListener (this, false);
    mPresetLabel.setText (mPreset.fileName, dontSendNotification);
    mPresetLabel.setColour (Label::textColourId, COLOR_BLACK);
    mPresetLabel.setJustificationType (Justification::centred);

    mCheckButton.addMouseListener (this, false);
    mImages.setDrawableButtonImages (mCheckButton, mIsInAssignableTag ? "CheckFull.svg" : "CheckEmpty.svg");

    addAndMakeVisible (mPresetLabel);
    addAndMakeVisible (mCheckButton);
}

PresetTaggerComponent::~PresetTaggerComponent()
{
}

//==============================================================================
void PresetTaggerComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (mIsInAssignableTag ? COLOR_GREY : COLOR_DARK);
    float cornerSize = getHeight() * CORNER_SIZE_RATIO;
    inGraphics.fillRoundedRectangle (getLocalBounds().toFloat(), cornerSize);
}

void PresetTaggerComponent::resized()
{
    auto area = getLocalBounds();

    juce::Rectangle<float> checkAreaProportion (CHECK_X / PRESET_WIDTH, CHECK_Y / ITEM_HEIGHT,
                                               CHECK_WIDTH / PRESET_WIDTH, CHECK_HEIGHT / ITEM_HEIGHT);

    mCheckButton.setBounds (area.getProportion (checkAreaProportion));

    mPresetLabel.setFont (Font ((area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO) - 2).boldened());
    mPresetLabel.setBounds (area.reduced (area.getHeight(), 0));
}

void PresetTaggerComponent::mouseDown (const MouseEvent& inEvent)
{
    if (onClick) { onClick (mPreset.indexValue); }
}
