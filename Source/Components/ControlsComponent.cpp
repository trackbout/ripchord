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
    mImages.setDrawableButtonImages (mVelocityDirectionButton, "Direction.svg");
    mImages.setDrawableButtonImages (mVelocityVarianceImage, "Variance.svg");

    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");

    mImages.setDrawableButtonImages (mTimingVarianceImage, "Variance.svg");
    mImages.setDrawableButtonImages (mTimingDirectionButton, "Direction.svg");
    mImages.setDrawableButtonImages (mTimingDepthImage, "Timing.svg");

    mVelocityDirectionButton.setTriggeredOnMouseDown (true);
    mTimingDirectionButton.setTriggeredOnMouseDown (true);

    mVelocityDirectionButton.onClick = [this]() { mControlsState.cycleVelocityDirection(); };
    mTimingDirectionButton.onClick = [this]() { mControlsState.cycleTimingDirection(); };

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
    mVelocityDepthImage.setBounds (VELOCITY_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDirectionButton.setBounds (VELOCITY_DIRECTION_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityVarianceImage.setBounds (VELOCITY_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDepthSlider.setBounds (VELOCITY_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mVelocityVarianceSlider.setBounds (VELOCITY_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);

    mShiftLeftButton.setBounds (SHIFT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTransposeButton.setBounds (TRANSPOSE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mShiftRightButton.setBounds (SHIFT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mTimingVarianceImage.setBounds (TIMING_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingDirectionButton.setBounds (TIMING_DIRECTION_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
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
        case (MessageCode::kTimingDirection): { handleToggleTimingDirection (inMessage); } break;
        case (MessageCode::kVelocityDirection): { handleToggleVelocityDirection (inMessage); } break;
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
        String transpose = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
        String timing = "Direction.svg";
        String velocity = "Direction.svg";
        mImages.setDrawableButtonImages (mTransposeButton, transpose);
        mImages.setDrawableButtonImages (mTimingDirectionButton, timing);
        mImages.setDrawableButtonImages (mVelocityDirectionButton, velocity);
    }
}

void ControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    String transpose = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
    mImages.setDrawableButtonImages (mTransposeButton, transpose);
}

void ControlsComponent::handleToggleTimingDirection (const DataMessage* inMessage)
{
    String timing = "Direction.svg";
    mImages.setDrawableButtonImages (mTimingDirectionButton, timing);
}

void ControlsComponent::handleToggleVelocityDirection (const DataMessage* inMessage)
{
    String velocity = "Direction.svg";
    mImages.setDrawableButtonImages (mVelocityDirectionButton, velocity);
}
