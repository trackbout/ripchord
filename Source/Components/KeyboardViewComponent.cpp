#include "KeyboardViewComponent.h"

//==============================================================================
KeyboardViewComponent::KeyboardViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mControlsState (mMainProcess.getControlsState()),
    mBrowserState (mMainProcess.getBrowserState()),
    mPresetState (mMainProcess.getPresetState()),
    mMidiState (mMainProcess.getMidiState()),
    mOutputKeyboard (inMainProcess),
    mInputKeyboard (inMainProcess),
    mPlayControls (inMainProcess),
    mEditControls (inMainProcess),
    mPresetName (inMainProcess),
    mChordName (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mImages.setDrawableButtonImages (mQuickFav, mBrowserState.isFavorite (mPresetState.getName()) ? "QuickFavON.svg" : "QuickFav.svg");
    mImages.setDrawableButtonImages (mMenuButton, "GearCircle.svg");
    mImages.setDrawableButtonImages (mPowerButton, mGlobalState.isPowerOn() ? "PowerON.svg" : "Power.svg");
    mImages.setDrawableButtonImages (mModeButton, mGlobalState.isEditMode() ? "ModeEDIT.svg" : "ModePLAY.svg");
    mImages.setDrawableButtonImages (mPresetsButton, "Presets.svg");
    mImages.setDrawableButtonImages (mInputKeyboardBg, "KeyboardBg.svg");
    mImages.setDrawableButtonImages (mOutputKeyboardBg, "KeyboardBg.svg");

    mOutputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    mInputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);

    mQuickFav.setTriggeredOnMouseDown (true);
    mQuickFav.onClick = [this]()
    {
        int indexValue = mBrowserState.getUnfilteredIndex (mPresetState.getName());
        mBrowserState.handleClickFavorite (indexValue);
    };

    mMenuButton.setTriggeredOnMouseDown (true);
    mMenuButton.onClick = [this]() { mGlobalState.toggleMenu(); };

    mPowerButton.setTriggeredOnMouseDown (true);
    mPowerButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        if (mMidiState.isRecording()) { return; }
        mGlobalState.togglePower();
    };

    mPresetsButton.setTriggeredOnMouseDown (true);
    mPresetsButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        if (mMidiState.isRecording()) { return; }
        mGlobalState.toggleView();
    };

    mModeButton.setTriggeredOnMouseDown (true);
    mModeButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        if (mMidiState.isRecording()) { return; }
        mGlobalState.toggleMode();
    };

    mOutputKeyboard.setBounds (KEYBOARD_X, OUTPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mInputKeyboard.setBounds (KEYBOARD_X, INPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mPlayControls.setBounds (SPACE, CONTROLS_Y, CONTROLS_WIDTH, CONTROLS_HEIGHT);
    mEditControls.setBounds (SPACE, CONTROLS_Y, CONTROLS_WIDTH, CONTROLS_HEIGHT);
    mPresetName.setBounds (TEXT_INPUT_X, FOOTER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);
    mChordName.setBounds (TEXT_INPUT_X, HEADER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT);

    addAndMakeVisible (mInputKeyboardBg);
    addAndMakeVisible (mOutputKeyboardBg);
    addAndMakeVisible (mInputKeyboardLabel);
    addAndMakeVisible (mOutputKeyboardLabel);

    addAndMakeVisible (mQuickFav);
    addAndMakeVisible (mMenuButton);
    addAndMakeVisible (mPowerButton);
    addAndMakeVisible (mPresetsButton);
    addAndMakeVisible (mModeButton);

    addAndMakeVisible (mOutputKeyboard);
    addAndMakeVisible (mInputKeyboard);
    addAndMakeVisible (mPlayControls);
    addChildComponent (mEditControls);
    addAndMakeVisible (mPresetName);
    addAndMakeVisible (mChordName);
}

KeyboardViewComponent::~KeyboardViewComponent()
{
}

//==============================================================================
void KeyboardViewComponent::paint (Graphics& inGraphics)
{
    auto mainArea = getLocalBounds();
    mInputKeyboardBg.setBounds (Styles::getRelativeBounds (mainArea, SPACE, INPUT_KEYBOARD_BG_Y, KEYBOARD_BG_WIDTH, KEYBOARD_BG_HEIGHT));
    mOutputKeyboardBg.setBounds (Styles::getRelativeBounds (mainArea, SPACE, OUTPUT_KEYBOARD_BG_Y, KEYBOARD_BG_WIDTH, KEYBOARD_BG_HEIGHT));
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
    mPlayControls.setTransform (AffineTransform::scale (scaleFactor));
    mEditControls.setTransform (AffineTransform::scale (scaleFactor));
    mPresetName.setTransform (AffineTransform::scale (scaleFactor));
    mChordName.setTransform (AffineTransform::scale (scaleFactor));

    mQuickFav.setBounds (Styles::getRelativeBounds (mainArea, FAV_BUTTON_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mMenuButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_BUTTON_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mPowerButton.setBounds (Styles::getRelativeBounds (mainArea, POWER_BUTTON_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mPresetsButton.setBounds (Styles::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mModeButton.setBounds (Styles::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
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
        case (MessageCode::kTogglePower): { handleTogglePower (inMessage); } break;
        case (MessageCode::kPresetFileFavorited): { handleToggleFavorite (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        default: { } break;
    };
}

void KeyboardViewComponent::handleToggleMode (const DataMessage* inMessage)
{
    mQuickFav.setVisible (mGlobalState.isPlayMode());
    mImages.setDrawableButtonImages (mModeButton, mGlobalState.isEditMode() ? "ModeEDIT.svg" : "ModePLAY.svg");
}

void KeyboardViewComponent::handleTogglePower (const DataMessage* inMessage)
{
    mImages.setDrawableButtonImages (mPowerButton, mGlobalState.isPowerOn() ? "PowerON.svg" : "Power.svg");
}

void KeyboardViewComponent::handleToggleFavorite (const DataMessage* inMessage)
{
    bool isFav = mBrowserState.isFavorite (mPresetState.getName());
    mImages.setDrawableButtonImages (mQuickFav, isFav ? "QuickFavON.svg" : "QuickFav.svg");
}

void KeyboardViewComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    bool isFav = mBrowserState.isFavorite (mPresetState.getName());
    mImages.setDrawableButtonImages (mQuickFav, isFav ? "QuickFavON.svg" : "QuickFav.svg");
}
