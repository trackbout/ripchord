#include "KeyboardViewComponent.h"

//==============================================================================
KeyboardViewComponent::KeyboardViewComponent()
{
    mOutputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    addAndMakeVisible (mOutputKeyboardLabel);
    addAndMakeVisible (mOutputKeyboard);

    mInputKeyboardLabel.setColour (Label::textColourId, COLOR_WHITE);
    addAndMakeVisible (mInputKeyboardLabel);
    addAndMakeVisible (mInputKeyboard);

    mOutputKeyboard.setBounds (KEYBOARD_X, OUTPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);
    mInputKeyboard.setBounds (KEYBOARD_X, INPUT_KEYBOARD_Y, KEYBOARD_WIDTH, KEYBOARD_HEIGHT);

    mImages.setDrawableButtonImages (mModeButton, "ModePLAY.svg", "", "", "", "ModeEDIT.svg", "", "", "");

    mModeButton.setTriggeredOnMouseDown (true);
    mModeButton.onClick = [this]() { DBG("YOLO"); };

    addAndMakeVisible (mModeButton);
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
}

//==============================================================================
