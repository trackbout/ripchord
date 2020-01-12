#include "KeyboardViewComponent.h"

//==============================================================================
KeyboardViewComponent::KeyboardViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mOutputKeyboard (inMainProcess),
    mInputKeyboard (inMainProcess),
    mPresetName (inMainProcess),
    mChordName (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mOutputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    mInputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);

    mImages.setDrawableButtonImages (mPresetsButton, "Presets.svg");
    mImages.setDrawableButtonImages (mModeButton, "ModePLAY.svg", "", "", "", "ModeEDIT.svg", "", "", "");
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg", "", "", "", "SaveON.svg", "", "", "");
    mImages.setDrawableButtonImages (mSuccess, "Success.svg");

    mPresetsButton.setTriggeredOnMouseDown (true);
    mPresetsButton.onClick = [this]() { mGlobalState.toggleView(); };

    mModeButton.setTriggeredOnMouseDown (true);
    mModeButton.onClick = [this]() { mGlobalState.toggleMode(); };

    mSaveButton.setTriggeredOnMouseDown (true);
    mSaveButton.onClick = [this]() { mPresetState.handleMouseClickOnSave(); };

    mOutputKeyboard.setBounds (KEYBOARD_X, OUTPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mInputKeyboard.setBounds (KEYBOARD_X, INPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mPresetName.setBounds (TEXT_INPUT_X, FOOTER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);
    mChordName.setBounds (TEXT_INPUT_X, HEADER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);

    addAndMakeVisible (mOutputKeyboardLabel);
    addAndMakeVisible (mInputKeyboardLabel);
    addAndMakeVisible (mPresetsButton);
    addAndMakeVisible (mModeButton);
    addChildComponent (mSaveButton);
    addChildComponent (mSuccess);

    addAndMakeVisible (mOutputKeyboard);
    addAndMakeVisible (mInputKeyboard);
    addAndMakeVisible (mPresetName);
    addAndMakeVisible (mChordName);
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
    mPresetName.setTransform (AffineTransform::scale(scaleFactor));
    mChordName.setTransform (AffineTransform::scale(scaleFactor));

    mModeButton.setBounds (Interface::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mPresetsButton.setBounds (Interface::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mSaveButton.setBounds (Interface::getRelativeBounds (mainArea, SAVE_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mSuccess.setBounds (Interface::getRelativeBounds (mainArea, SAVE_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
}

//==============================================================================
void KeyboardViewComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kModeUpdated): { handleModeUpdated (inMessage); } break;
        case (MessageCode::kPresetNameUpdated): { handlePresetNameUpdated (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handleEditModeOutputNotes (inMessage); } break;
        default: { } break;
    };
}

void KeyboardViewComponent::handleModeUpdated (const DataMessage* inMessage)
{
    mSaveButton.setVisible (mGlobalState.isEditMode());
    mModeButton.setToggleState (mGlobalState.isEditMode(), dontSendNotification);
}

void KeyboardViewComponent::handlePresetNameUpdated (const DataMessage* inMessage)
{
    mSaveButton.setToggleState (mPresetState.isPresetSaveable(), dontSendNotification);
}

void KeyboardViewComponent::handleEditModeOutputNotes (const DataMessage* inMessage)
{
    mSaveButton.setToggleState (mPresetState.isPresetSaveable(), dontSendNotification);
}
