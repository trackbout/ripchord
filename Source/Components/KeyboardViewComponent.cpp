#include "KeyboardViewComponent.h"

//==============================================================================
KeyboardViewComponent::KeyboardViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mControlsState (mMainProcess.getControlsState()),
    mMidiState (mMainProcess.getMidiState()),
    mOutputKeyboard (inMainProcess),
    mInputKeyboard (inMainProcess),
    mPlayControls (inMainProcess),
    mEditControls (inMainProcess),
    mPresetName (inMainProcess),
    mChordName (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mOutputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    mInputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);

    mImages.setDrawableButtonImages (mPresetsButton, "Presets.svg");
    mImages.setDrawableButtonImages (mModeButton, "ModePLAY.svg");

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

    addAndMakeVisible (mOutputKeyboardLabel);
    addAndMakeVisible (mInputKeyboardLabel);
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
    mPlayControls.setTransform (AffineTransform::scale (scaleFactor));
    mEditControls.setTransform (AffineTransform::scale (scaleFactor));
    mPresetName.setTransform (AffineTransform::scale (scaleFactor));
    mChordName.setTransform (AffineTransform::scale (scaleFactor));

    mModeButton.setBounds (Styles::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mPresetsButton.setBounds (Styles::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
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
        default: { } break;
    };
}

void KeyboardViewComponent::handleToggleMode (const DataMessage* inMessage)
{
    mImages.setDrawableButtonImages (mModeButton, mGlobalState.isEditMode() ? "ModeEDIT.svg" : "ModePLAY.svg");
}
