#include "KeyboardViewComponent.h"

//==============================================================================
KeyboardViewComponent::KeyboardViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mOutputKeyboard (inMainProcess),
    mInputKeyboard (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mOutputKeyboard.setBounds (KEYBOARD_X, OUTPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mInputKeyboard.setBounds (KEYBOARD_X, INPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);

    mOutputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    mInputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);

    mImages.setDrawableButtonImages (mModeButton, "ModePLAY.svg", "", "", "", "ModeEDIT.svg", "", "", "");
    mImages.setDrawableButtonImages (mPresetsButton, "Presets.svg");

    mModeButton.setTriggeredOnMouseDown (true);
    mModeButton.onClick = [this]() { mGlobalState.toggleMode(); };

    mPresetsButton.setTriggeredOnMouseDown (true);
    mPresetsButton.onClick = [this]() { mGlobalState.toggleView(); };

    mPresetNameInput.setTextToShowWhenEmpty ("name this preset...", COLOR_GREY_MEDIUM);
    mPresetNameInput.setColour (TextEditor::backgroundColourId, COLOR_GREY_LIGHTER);
    mPresetNameInput.setJustification (Justification::centred);
    mPresetNameInput.setWantsKeyboardFocus (true);
    mPresetNameInput.onReturnKey = [this]() { grabKeyboardFocus(); };
    mPresetNameInput.onTextChange = [this]() { mPresetState.handlePresetNameTextChanged (mPresetNameInput.getText()); };

    addAndMakeVisible (mOutputKeyboard);
    addAndMakeVisible (mInputKeyboard);
    addAndMakeVisible (mOutputKeyboardLabel);
    addAndMakeVisible (mInputKeyboardLabel);
    addAndMakeVisible (mModeButton);
    addAndMakeVisible (mPresetsButton);
    addAndMakeVisible (mPresetArrows);
    addChildComponent (mPresetNameInput);
}

KeyboardViewComponent::~KeyboardViewComponent()
{
}

//==============================================================================
void KeyboardViewComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY_DARK);
    auto mainArea = getLocalBounds();

    auto outputBgArea = Interface::getRelativeBounds (mainArea, SPACE, OUTPUT_KEYBOARD_BG_Y,
                                                      KEYBOARD_BG_WIDTH, KEYBOARD_BG_HEIGHT).toFloat();

    auto inputBgArea = Interface::getRelativeBounds (mainArea, SPACE, INPUT_KEYBOARD_BG_Y,
                                                     KEYBOARD_BG_WIDTH, KEYBOARD_BG_HEIGHT).toFloat();

    float cornerSize = outputBgArea.getHeight() * (CORNER_SIZE_RATIO * (ITEM_HEIGHT / KEYBOARD_BG_HEIGHT));
    inGraphics.fillRoundedRectangle (outputBgArea, cornerSize);
    inGraphics.fillRoundedRectangle (inputBgArea, cornerSize);
}

void KeyboardViewComponent::resized()
{
    auto mainArea = getLocalBounds();

    mOutputKeyboardLabel.setBounds (Interface::getRelativeBounds (mainArea, KEYBOARD_LABEL_X, OUTPUT_LABEL_Y,
                                                                  KEYBOARD_LABEL_WIDTH, KEYBOARD_LABEL_HEIGHT));

    mInputKeyboardLabel.setBounds (Interface::getRelativeBounds (mainArea, KEYBOARD_LABEL_X, INPUT_LABEL_Y,
                                                                 KEYBOARD_LABEL_WIDTH, KEYBOARD_LABEL_HEIGHT));

    auto keyboardLabelFont = Font (mOutputKeyboardLabel.getHeight()).boldened();
    mOutputKeyboardLabel.setFont (keyboardLabelFont);
    mInputKeyboardLabel.setFont (keyboardLabelFont);

    float scaleFactor = (float) getWidth() / EDITOR_WIDTH;
    mOutputKeyboard.setTransform (AffineTransform::scale(scaleFactor));
    mInputKeyboard.setTransform (AffineTransform::scale(scaleFactor));

    mModeButton.setBounds (Interface::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mPresetsButton.setBounds (Interface::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));

    auto presetArrowsBounds = Interface::getRelativeBounds (mainArea, TEXT_INPUT_X, FOOTER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);
    mPresetNameInput.setBounds (presetArrowsBounds);
    mPresetArrows.setBounds (presetArrowsBounds);

    auto textInputFont = Font (mPresetNameInput.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO).boldened();
    mPresetNameInput.applyFontToAllText (textInputFont);

    auto& presetName = mPresetNameInput;
    float presetExtra = presetName.getHeight() - presetName.getFont().getHeight() - presetName.getBorder().getTopAndBottom();
    mPresetNameInput.setIndents (5, (int) (presetExtra * 0.5f));
}

//==============================================================================
void KeyboardViewComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kModeUpdated): { handleModeUpdated (inMessage); } break;
        case (MessageCode::kPresetNameUpdated): { handlePresetNameUpdated (inMessage); } break;
        default: { } break;
    };
}

void KeyboardViewComponent::handleModeUpdated (const DataMessage* inMessage)
{
    mModeButton.setToggleState (mGlobalState.isEditMode(), dontSendNotification);
    mPresetNameInput.setVisible (mGlobalState.isEditMode());
}

void KeyboardViewComponent::handlePresetNameUpdated (const DataMessage* inMessage)
{
    String nextPresetName = inMessage->messageVar1;
    mPresetArrows.updateTextLabel (nextPresetName);
}
