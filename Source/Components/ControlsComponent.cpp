#include "ControlsComponent.h"

//==============================================================================
ControlsComponent::ControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mControlsState (mMainProcess.getControlsState()),
    mMidiState (mMainProcess.getMidiState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mVelocityDepthImage, "Velocity.svg");
    mImages.setDrawableButtonImages (mVelocityAlternateButton, "Alternate.svg");
    mImages.setDrawableButtonImages (mVelocityVarianceImage, "Variance.svg");

    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");

    mImages.setDrawableButtonImages (mTimingVarianceImage, "Variance.svg");
    mImages.setDrawableButtonImages (mTimingAlternateButton, "Alternate.svg");
    mImages.setDrawableButtonImages (mTimingDepthImage, "Timing.svg");

    mVelocityAlternateButton.setTriggeredOnMouseDown (true);
    mTimingAlternateButton.setTriggeredOnMouseDown (true);

    mVelocityDepthSlider.setRange (0, 100);
    mVelocityDepthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mVelocityDepthSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mVelocityVarianceSlider.setRange (0, 100);
    mVelocityVarianceSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mVelocityVarianceSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mTimingDepthSlider.setRange (0, 100);
    mTimingDepthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mTimingDepthSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mTimingVarianceSlider.setRange (0, 100);
    mTimingVarianceSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mTimingVarianceSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mShiftLeftButton.setTriggeredOnMouseDown (true);
    mTransposeButton.setTriggeredOnMouseDown (true);
    mShiftRightButton.setTriggeredOnMouseDown (true);

    mShiftLeftButton.onClick = [this]()
    {
        if (isTransposeShiftDisabled()) { return; }
        mControlsState.handleMouseClickOnShiftLeft();
    };

    mTransposeButton.onClick = [this]()
    {
        if (isTransposeToggleDisabled()) { return; }
        mControlsState.toggleTranspose();
    };

    mShiftRightButton.onClick = [this]()
    {
        if (isTransposeShiftDisabled()) { return; }
        mControlsState.handleMouseClickOnShiftRight();
    };

    addAndMakeVisible (mVelocityDepthImage);
    addAndMakeVisible (mVelocityAlternateButton);
    addAndMakeVisible (mVelocityVarianceImage);
    addAndMakeVisible (mVelocityDepthSlider);
    addAndMakeVisible (mVelocityVarianceSlider);

    addAndMakeVisible (mShiftLeftButton);
    addAndMakeVisible (mTransposeButton);
    addAndMakeVisible (mShiftRightButton);

    addAndMakeVisible (mTimingVarianceImage);
    addAndMakeVisible (mTimingAlternateButton);
    addAndMakeVisible (mTimingDepthImage);
    addAndMakeVisible (mTimingVarianceSlider);
    addAndMakeVisible (mTimingDepthSlider);
}

ControlsComponent::~ControlsComponent()
{
}

//==============================================================================
void ControlsComponent::resized()
{
    mVelocityDepthImage.setBounds (VELOCITY_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityAlternateButton.setBounds (VELOCITY_ALTERNATE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityVarianceImage.setBounds (VELOCITY_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDepthSlider.setBounds (VELOCITY_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mVelocityVarianceSlider.setBounds (VELOCITY_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);

    mShiftLeftButton.setBounds (SHIFT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTransposeButton.setBounds (TRANSPOSE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mShiftRightButton.setBounds (SHIFT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mTimingVarianceImage.setBounds (TIMING_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingAlternateButton.setBounds (TIMING_ALTERNATE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingDepthImage.setBounds (TIMING_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingVarianceSlider.setBounds (TIMING_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mTimingDepthSlider.setBounds (TIMING_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
}

//==============================================================================
void ControlsComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void ControlsComponent::handleToggleMode (const DataMessage* inMessage)
{
    if (mGlobalState.isEditMode())
    {
        mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    }

    if (mGlobalState.isPlayMode())
    {
        String svgPath = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
        mImages.setDrawableButtonImages (mTransposeButton, svgPath);
    }
}

void ControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    String svgPath = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
    mImages.setDrawableButtonImages (mTransposeButton, svgPath);
}

bool ControlsComponent::isTransposeShiftDisabled()
{
    if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return true; }
    if (mControlsState.getActiveTransposeNote() > 0) { return true; }
    if (mGlobalState.isEditMode()) { return true; }
    return false;
}

bool ControlsComponent::isTransposeToggleDisabled()
{
    if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return true; }
    if (mGlobalState.isEditMode()) { return true; }
    return false;
}
