#include "KeyboardViewComponent.h"

//==============================================================================
KeyboardViewComponent::KeyboardViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mMidiState (mMainProcess.getMidiState()),
    mOutputKeyboard (inMainProcess),
    mInputKeyboard (inMainProcess),
    mPresetName (inMainProcess),
    mChordName (inMainProcess),
    mControls (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mOutputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    mInputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);

    mImages.setDrawableButtonImages (mPresetsButton, "Presets.svg");
    mImages.setDrawableButtonImages (mModeButton, "ModePLAY.svg");

    mPresetsButton.setTriggeredOnMouseDown (true);
    mPresetsButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() < 1) { mGlobalState.toggleView(); }
    };

    mModeButton.setTriggeredOnMouseDown (true);
    mModeButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() < 1) { mGlobalState.toggleMode(); }
    };

    mAllWhiteButton.setTriggeredOnMouseDown (true);
    mAllWhiteButton.onClick = [this]()
    {
        DBG ("WHITE");
    };

    mEditLeftButton.setTriggeredOnMouseDown (true);
    mEditLeftButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mPresetState.handleMouseClickOnEditLeft();
    };

    mSaveButton.setTriggeredOnMouseDown (true);
    mSaveButton.onClick = [this]() { mPresetState.handleMouseClickOnSave(); };

    mEditRightButton.setTriggeredOnMouseDown (true);
    mEditRightButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mPresetState.handleMouseClickOnEditRight();
    };

    mAllBlackButton.setTriggeredOnMouseDown (true);
    mAllBlackButton.onClick = [this]()
    {
        DBG ("BLACK");
    };

    mOutputKeyboard.setBounds (KEYBOARD_X, OUTPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mInputKeyboard.setBounds (KEYBOARD_X, INPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mPresetName.setBounds (TEXT_INPUT_X, FOOTER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);
    mChordName.setBounds (TEXT_INPUT_X, HEADER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);
    mControls.setBounds (SPACE, CONTROLS_Y, CONTROLS_WIDTH, CONTROLS_HEIGHT);

    mImages.setDrawableButtonImages (mAllWhiteButton, "AllWhite.svg", "", "AllWhiteON.svg", "");
    mImages.setDrawableButtonImages (mAllBlackButton, "AllBlack.svg", "", "AllBlackON.svg", "");
    mImages.setDrawableButtonImages (mEditRightButton, "ShiftRight.svg", "", "EditRightON.svg", "");
    mImages.setDrawableButtonImages (mEditLeftButton, "ShiftLeft.svg", "", "EditLeftON.svg", "");
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
    mImages.setDrawableButtonImages (mSuccess, "Success.svg");

    addAndMakeVisible (mOutputKeyboardLabel);
    addAndMakeVisible (mInputKeyboardLabel);
    addAndMakeVisible (mPresetsButton);
    addAndMakeVisible (mModeButton);

    addAndMakeVisible (mOutputKeyboard);
    addAndMakeVisible (mInputKeyboard);
    addAndMakeVisible (mPresetName);
    addAndMakeVisible (mChordName);
    addAndMakeVisible (mControls);

    addChildComponent (mAllWhiteButton);
    addChildComponent (mAllBlackButton);
    addChildComponent (mEditRightButton);
    addChildComponent (mEditLeftButton);
    addChildComponent (mSaveButton);
    addChildComponent (mSuccess);
}

KeyboardViewComponent::~KeyboardViewComponent()
{
}

//==============================================================================
void KeyboardViewComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY_DARK);
    auto mainArea = getLocalBounds();

    auto outputBgArea = Styles::getRelativeBounds (mainArea, SPACE, OUTPUT_KEYBOARD_BG_Y,
                                                   KEYBOARD_BG_WIDTH, KEYBOARD_BG_HEIGHT).toFloat();

    auto inputBgArea = Styles::getRelativeBounds (mainArea, SPACE, INPUT_KEYBOARD_BG_Y,
                                                  KEYBOARD_BG_WIDTH, KEYBOARD_BG_HEIGHT).toFloat();

    float cornerSize = outputBgArea.getHeight() * (CORNER_SIZE_RATIO * (ITEM_HEIGHT / KEYBOARD_BG_HEIGHT));
    inGraphics.fillRoundedRectangle (outputBgArea, cornerSize);
    inGraphics.fillRoundedRectangle (inputBgArea, cornerSize);
}

void KeyboardViewComponent::resized()
{
    auto mainArea = getLocalBounds();

    mOutputKeyboardLabel.setBounds (Styles::getRelativeBounds (mainArea, KEYBOARD_LABEL_X, OUTPUT_LABEL_Y,
                                                               KEYBOARD_LABEL_WIDTH, KEYBOARD_LABEL_HEIGHT));

    mInputKeyboardLabel.setBounds (Styles::getRelativeBounds (mainArea, KEYBOARD_LABEL_X, INPUT_LABEL_Y,
                                                              KEYBOARD_LABEL_WIDTH, KEYBOARD_LABEL_HEIGHT));

    auto keyboardLabelFont = Font (mOutputKeyboardLabel.getHeight()).boldened();
    mOutputKeyboardLabel.setFont (keyboardLabelFont);
    mInputKeyboardLabel.setFont (keyboardLabelFont);

    float scaleFactor = (float) getWidth() / EDITOR_WIDTH;
    mOutputKeyboard.setTransform (AffineTransform::scale (scaleFactor));
    mInputKeyboard.setTransform (AffineTransform::scale (scaleFactor));
    mPresetName.setTransform (AffineTransform::scale (scaleFactor));
    mChordName.setTransform (AffineTransform::scale (scaleFactor));
    mControls.setTransform (AffineTransform::scale (scaleFactor));

    mModeButton.setBounds (Styles::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mPresetsButton.setBounds (Styles::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mAllWhiteButton.setBounds (Styles::getRelativeBounds (mainArea, ALL_WHITE_X, SAVE_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mAllBlackButton.setBounds (Styles::getRelativeBounds (mainArea, ALL_BLACK_X, SAVE_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mEditRightButton.setBounds (Styles::getRelativeBounds (mainArea, EDIT_RIGHT_X, SAVE_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mEditLeftButton.setBounds (Styles::getRelativeBounds (mainArea, EDIT_LEFT_X, SAVE_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mSaveButton.setBounds (Styles::getRelativeBounds (mainArea, SAVE_X, SAVE_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mSuccess.setBounds (Styles::getRelativeBounds (mainArea, SAVE_X, SAVE_Y, ITEM_HEIGHT, ITEM_HEIGHT));
}

//==============================================================================
bool KeyboardViewComponent::keyPressed (const KeyPress& inKey)
{
    if (mGlobalState.isPresetView() || mGlobalState.isEditMode()) { return false; }

    auto keyCode = inKey.getKeyCode();

    if (keyCode == KeyPress::leftKey || keyCode == KeyPress::upKey)
    {
        mPresetName.triggerLeftArrow();
    }

    if (keyCode == KeyPress::rightKey || keyCode == KeyPress::downKey)
    {
        mPresetName.triggerRightArrow();
    }

    return false;
}

//==============================================================================
void KeyboardViewComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileSaved): { handlePresetFileSaved (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handlePresetModified (inMessage); } break;
        case (MessageCode::kPresetNameTextChanged): { handlePresetModified (inMessage); } break;
        case (MessageCode::kChordNameTextChanged): { handlePresetModified (inMessage); } break;
        case (MessageCode::kEditModeShiftArrow): { handlePresetModified (inMessage); } break;
        default: { } break;
    };
}

void KeyboardViewComponent::handleToggleMode (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mSaveButton.setVisible (mGlobalState.isEditMode());
    mAllWhiteButton.setVisible (mGlobalState.isEditMode());
    mAllBlackButton.setVisible (mGlobalState.isEditMode());
    mEditLeftButton.setVisible (mGlobalState.isEditMode());
    mEditRightButton.setVisible (mGlobalState.isEditMode());
    mImages.setDrawableButtonImages (mModeButton, mGlobalState.isEditMode() ? "ModeEDIT.svg" : "ModePLAY.svg");

    bool isPresetSaveable = mPresetState.isPresetModified() && mPresetState.isPresetValid();
    mImages.setDrawableButtonImages (mSaveButton, isPresetSaveable ? "SaveON.svg" : "Save.svg");
}

void KeyboardViewComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
}

void KeyboardViewComponent::handlePresetFileSaved (const DataMessage* inMessage)
{
    mSuccess.setVisible (true);
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
}

void KeyboardViewComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mImages.setDrawableButtonImages (mSaveButton, "Save.svg");
}

void KeyboardViewComponent::handlePresetModified (const DataMessage* inMessage)
{
    mSuccess.setVisible (false);
    mImages.setDrawableButtonImages (mSaveButton, mPresetState.isPresetValid() ? "SaveON.svg" : "Save.svg");
}
