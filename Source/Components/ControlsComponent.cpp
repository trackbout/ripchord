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
    mImages.setDrawableButtonImages (mVelocityVarianceImage, "Variance.svg");

    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");

    mImages.setDrawableButtonImages (mTimingVarianceImage, "Variance.svg");
    mImages.setDrawableButtonImages (mTimingDepthImage, "Timing.svg");

    mVelocityDirectionButton.setTriggeredOnMouseDown (true);
    mTimingDirectionButton.setTriggeredOnMouseDown (true);

    mVelocityDirectionButton.onClick = [this]() {
        if (mControlsState.getVelocityDepth() == 0) { return; }
        mControlsState.cycleVelocityDirection();
    };

    mTimingDirectionButton.onClick = [this]() {
        if (mControlsState.getTimingDepth() == 0) { return; }
        mControlsState.cycleTimingDirection();
    };

    mVelocityDepthSlider.addListener (this);
    mVelocityDepthSlider.setRange (0, 1);
    mVelocityDepthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mVelocityDepthSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mVelocityVarianceSlider.addListener (this);
    mVelocityVarianceSlider.setRange (0, 1);
    mVelocityVarianceSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mVelocityVarianceSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mTimingDepthSlider.addListener (this);
    mTimingDepthSlider.setRange (0, 1);
    mTimingDepthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mTimingDepthSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mTimingVarianceSlider.addListener (this);
    mTimingVarianceSlider.setRange (0, 1);
    mTimingVarianceSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mTimingVarianceSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mShiftLeftButton.setTriggeredOnMouseDown (true);
    mTransposeButton.setTriggeredOnMouseDown (true);
    mShiftRightButton.setTriggeredOnMouseDown (true);

    mShiftLeftButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mControlsState.handleMouseClickOnShiftLeft();
    };

    mTransposeButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mControlsState.toggleTranspose();
    };

    mShiftRightButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mControlsState.handleMouseClickOnShiftRight();
    };

    addAndMakeVisible (mVelocityDepthImage);
    addAndMakeVisible (mVelocityDirectionButton);
    addAndMakeVisible (mVelocityVarianceImage);
    addAndMakeVisible (mVelocityDepthSlider);
    addAndMakeVisible (mVelocityVarianceSlider);

    addAndMakeVisible (mShiftLeftButton);
    addAndMakeVisible (mTransposeButton);
    addAndMakeVisible (mShiftRightButton);

    addAndMakeVisible (mTimingVarianceImage);
    addAndMakeVisible (mTimingDirectionButton);
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
    mVelocityDirectionButton.setBounds (VELOCITY_DIRECTION_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDepthImage.setBounds (VELOCITY_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityVarianceImage.setBounds (VELOCITY_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDepthSlider.setBounds (VELOCITY_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mVelocityVarianceSlider.setBounds (VELOCITY_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);

    mShiftLeftButton.setBounds (SHIFT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTransposeButton.setBounds (TRANSPOSE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mShiftRightButton.setBounds (SHIFT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mTimingVarianceImage.setBounds (TIMING_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingDepthImage.setBounds (TIMING_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingVarianceSlider.setBounds (TIMING_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mTimingDepthSlider.setBounds (TIMING_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mTimingDirectionButton.setBounds (TIMING_DIRECTION_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
}

//==============================================================================
void ControlsComponent::sliderValueChanged (Slider* inSlider)
{
    if (inSlider == &mVelocityDepthSlider)
    {
        mControlsState.handleVelocityDepthSlider (mVelocityDepthSlider.getValue());
    }

    if (inSlider == &mVelocityVarianceSlider)
    {
        mControlsState.handleVelocityVarianceSlider (mVelocityVarianceSlider.getValue());
    }

    if (inSlider == &mTimingVarianceSlider)
    {
        mControlsState.handleTimingVarianceSlider (mTimingVarianceSlider.getValue());
    }

    if (inSlider == &mTimingDepthSlider)
    {
        mControlsState.handleTimingDepthSlider (mTimingDepthSlider.getValue());
    }
}

//==============================================================================
void ControlsComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        case (MessageCode::kTimingDepth): { handleTimingDepth (inMessage); } break;
        case (MessageCode::kTimingDirection): { handleTimingDirection (inMessage); } break;
        case (MessageCode::kVelocityDepth): { handleVelocityDepth (inMessage); } break;
        case (MessageCode::kVelocityDirection): { handleVelocityDirection (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void ControlsComponent::handleToggleMode (const DataMessage* inMessage)
{
    if (mGlobalState.isEditMode()) { setVisible (false); }

    if (mGlobalState.isPlayMode())
    {
        setVisible (true);
        updateTransposeButton();
        updateTimingDirectionButton();
        updateVelocityDirectionButton();
    }
}

void ControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    updateTransposeButton();
}

void ControlsComponent::handleTimingDepth (const DataMessage* inMessage)
{
    updateTimingDirectionButton();
}

void ControlsComponent::handleTimingDirection (const DataMessage* inMessage)
{
    updateTimingDirectionButton();
}

void ControlsComponent::handleVelocityDepth (const DataMessage* inMessage)
{
    updateVelocityDirectionButton();
}

void ControlsComponent::handleVelocityDirection (const DataMessage* inMessage)
{
    updateVelocityDirectionButton();
}

void ControlsComponent::updateTransposeButton()
{
    String buttonImage = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
    mImages.setDrawableButtonImages (mTransposeButton, buttonImage);
}

void ControlsComponent::updateTimingDirectionButton()
{
    String buttonImage = "Direction.svg";
    String timingDirection = mControlsState.getTimingDirection();

    if (mControlsState.getTimingDepth() == 0) { buttonImage = "Direction.svg"; }
    else if (timingDirection == "LTR") { buttonImage = "DirectionAB.svg"; }
    else if (timingDirection == "RTL") { buttonImage = "DirectionBA.svg"; }
    else if (timingDirection == "LTR_RTL") { buttonImage = "DirectionABBA.svg"; }
    else if (timingDirection == "RTL_LTR") { buttonImage = "DirectionBAAB.svg"; }

    mImages.setDrawableButtonImages (mTimingDirectionButton, buttonImage);
}

void ControlsComponent::updateVelocityDirectionButton()
{
    String buttonImage = "Direction.svg";
    String velocityDirection = mControlsState.getVelocityDirection();

    if (mControlsState.getVelocityDepth() == 0) { buttonImage = "Direction.svg"; }
    else if (velocityDirection == "HTS") { buttonImage = "DirectionAB.svg"; }
    else if (velocityDirection == "STH") { buttonImage = "DirectionBA.svg"; }
    else if (velocityDirection == "HTS_STH") { buttonImage = "DirectionABBA.svg"; }
    else if (velocityDirection == "STH_HTS") { buttonImage = "DirectionBAAB.svg"; }

    mImages.setDrawableButtonImages (mVelocityDirectionButton, buttonImage);
}
