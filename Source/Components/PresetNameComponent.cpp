#include "PresetNameComponent.h"

//==============================================================================
PresetNameComponent::PresetNameComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mImages.setDrawableButtonImages (mLeftArrowButton, "Prev.svg", "", "PrevON.svg", "");
    mImages.setDrawableButtonImages (mRightArrowButton, "Next.svg", "", "NextON.svg", "");

    mLeftArrowButton.setTriggeredOnMouseDown (true);
    mRightArrowButton.setTriggeredOnMouseDown (true);

    mLeftArrowButton.onClick = [this]() { if (onLeftArrowClick) onLeftArrowClick(); };
    mRightArrowButton.onClick = [this]() { if (onRightArrowClick) onRightArrowClick(); };

    mPresetNameLabel.setJustificationType (Justification::centred);

    mPresetNameInput.setTextToShowWhenEmpty ("name this preset...", COLOR_GREY_MEDIUM);
    mPresetNameInput.setColour (TextEditor::backgroundColourId, COLOR_GREY_LIGHTER);
    mPresetNameInput.setJustification (Justification::centred);
    mPresetNameInput.setWantsKeyboardFocus (true);
    mPresetNameInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mPresetNameInput.onTextChange = [this]()
    {
        mPresetState.handlePresetNameTextChanged (mPresetNameInput.getText());
    };

    addAndMakeVisible (mLeftArrowButton);
    addAndMakeVisible (mRightArrowButton);
    addAndMakeVisible (mPresetNameLabel);
    addChildComponent (mPresetNameInput);
}

PresetNameComponent::~PresetNameComponent()
{
}

//==============================================================================
void PresetNameComponent::resized()
{
    auto area = getLocalBounds();
    int arrowWidth = area.proportionOfWidth (ARROW_WIDTH / TEXT_INPUT_WIDTH);
    auto textFont = Font (area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO).boldened();

    mPresetNameInput.setFont (textFont);
    mPresetNameLabel.setFont (textFont);

    mPresetNameInput.setBounds (area);
    mLeftArrowButton.setBounds (area.removeFromLeft (arrowWidth));
    mRightArrowButton.setBounds (area.removeFromRight (arrowWidth));
    mPresetNameLabel.setBounds (area);

    auto& input = mPresetNameInput;
    float extra = input.getHeight() - input.getFont().getHeight() - input.getBorder().getTopAndBottom();
    mPresetNameInput.setIndents (5, (int) (extra * 0.5f));
}

//==============================================================================
void PresetNameComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kModeUpdated): { handleModeUpdated (inMessage); } break;
        case (MessageCode::kPresetNameUpdated): { handlePresetNameUpdated (inMessage); } break;
        default: { } break;
    };
}

void PresetNameComponent::handleModeUpdated (const DataMessage* inMessage)
{
    mPresetNameInput.setVisible (mGlobalState.isEditMode());
}

void PresetNameComponent::handlePresetNameUpdated (const DataMessage* inMessage)
{
    String nextPresetName = inMessage->messageVar1;
    mPresetNameLabel.setText (nextPresetName, dontSendNotification);
}
