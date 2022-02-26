#include "PlayControlsComponent.h"

//==============================================================================
PlayControlsComponent::PlayControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mControlsState (mMainProcess.getControlsState()),
    mMidiState (mMainProcess.getMidiState()),
    mRecordedMidi (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mMidiState.DataMessageBroadcaster::addListener (this, ListenerType::kAsync);

    mImages.setDrawableButtonImages (mRecordButton, "Record.svg");
    mImages.setDrawableButtonImages (mVelocityDepthImage, "Velocity.svg");
    mImages.setDrawableButtonImages (mVelocityVarianceImage, "Variance.svg");
    mImages.setDrawableButtonImages (mShiftLeftButton, "MoveLeft.svg", "", "MoveLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "MoveRight.svg", "", "MoveRightON.svg", "");
    mImages.setDrawableButtonImages (mDelayVarianceImage, "Variance.svg");
    mImages.setDrawableButtonImages (mDelayDepthImage, "Delay.svg");

    mRecordButton.setTriggeredOnMouseDown (true);
    mVelocityDirectionButton.setTriggeredOnMouseDown (true);
    mShiftLeftButton.setTriggeredOnMouseDown (true);
    mTransposeButton.setTriggeredOnMouseDown (true);
    mShiftRightButton.setTriggeredOnMouseDown (true);
    mDelayDirectionButton.setTriggeredOnMouseDown (true);

    mRecordButton.onClick = [this]()
    {
        if (!mControlsState.isRecordOn()) { mMidiState.clearRecordedSequence(); }
        if (mMidiState.isRecording()) { mMidiState.stopRecording(); }
        mControlsState.toggleRecord();
    };

    mVelocityDirectionButton.onClick = [this]()
    {
        if (mControlsState.getVelocityDepth() == 0) { return; }
        mControlsState.cycleVelocityDirection();
    };

    mDelayDirectionButton.onClick = [this]()
    {
        if (mControlsState.getDelayDepth() == 0) { return; }
        mControlsState.cycleDelayDirection();
    };

    mVelocityDepthSlider.addListener (this);
    mVelocityDepthSlider.setRange (0, 100000);
    mVelocityDepthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mVelocityDepthSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mVelocityVarianceSlider.addListener (this);
    mVelocityVarianceSlider.setRange (0, 100000);
    mVelocityVarianceSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mVelocityVarianceSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mDelayDepthSlider.addListener (this);
    mDelayDepthSlider.setRange (0, 100000);
    mDelayDepthSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mDelayDepthSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mDelayVarianceSlider.addListener (this);
    mDelayVarianceSlider.setRange (0, 100000);
    mDelayVarianceSlider.setSliderStyle (Slider::RotaryVerticalDrag);
    mDelayVarianceSlider.setTextBoxStyle (Slider::NoTextBox, true, 0, 0);

    mShiftLeftButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mControlsState.handleMouseDownOnShiftLeft();
    };

    mTransposeButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mControlsState.toggleTranspose();
    };

    mShiftRightButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mControlsState.handleMouseDownOnShiftRight();
    };

    addAndMakeVisible (mRecordButton);

    addAndMakeVisible (mVelocityDepthImage);
    addAndMakeVisible (mVelocityDirectionButton);
    addAndMakeVisible (mVelocityVarianceImage);
    addAndMakeVisible (mVelocityDepthSlider);
    addAndMakeVisible (mVelocityVarianceSlider);

    addAndMakeVisible (mShiftLeftButton);
    addAndMakeVisible (mTransposeButton);
    addAndMakeVisible (mShiftRightButton);

    addAndMakeVisible (mDelayVarianceImage);
    addAndMakeVisible (mDelayDirectionButton);
    addAndMakeVisible (mDelayDepthImage);
    addAndMakeVisible (mDelayVarianceSlider);
    addAndMakeVisible (mDelayDepthSlider);

    addAndMakeVisible (mRecordedMidi);
}

PlayControlsComponent::~PlayControlsComponent()
{
}

//==============================================================================
void PlayControlsComponent::resized()
{
    mRecordButton.setBounds (RECORD_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mVelocityDirectionButton.setBounds (VELOCITY_DIRECTION_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDepthImage.setBounds (VELOCITY_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityVarianceImage.setBounds (VELOCITY_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityDepthSlider.setBounds (VELOCITY_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mVelocityVarianceSlider.setBounds (VELOCITY_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);

    mShiftLeftButton.setBounds (SHIFT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTransposeButton.setBounds (TRANSPOSE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mShiftRightButton.setBounds (SHIFT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mDelayVarianceImage.setBounds (DELAY_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mDelayDepthImage.setBounds (DELAY_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mDelayVarianceSlider.setBounds (DELAY_VARIANCE_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mDelayDepthSlider.setBounds (DELAY_DEPTH_X - SLIDER_X_OFFSET, SLIDER_Y, SLIDER_SIZE, SLIDER_SIZE);
    mDelayDirectionButton.setBounds (DELAY_DIRECTION_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mRecordedMidi.setBounds (RECORDED_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
}

//==============================================================================
void PlayControlsComponent::sliderValueChanged (Slider* inSlider)
{
    if (inSlider == &mVelocityDepthSlider)
    {
        mControlsState.handleVelocityDepthSlider (mVelocityDepthSlider.getValue());
    }

    if (inSlider == &mVelocityVarianceSlider)
    {
        mControlsState.handleVelocityVarianceSlider (mVelocityVarianceSlider.getValue());
    }

    if (inSlider == &mDelayVarianceSlider)
    {
        mControlsState.handleDelayVarianceSlider (mDelayVarianceSlider.getValue());
    }

    if (inSlider == &mDelayDepthSlider)
    {
        mControlsState.handleDelayDepthSlider (mDelayDepthSlider.getValue());
    }
}

//==============================================================================
void PlayControlsComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kIsRecording): { handleIsRecording (inMessage); } break;
        case (MessageCode::kToggleRecord): { handleToggleRecord (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        case (MessageCode::kDelayDepth): { handleDelayDepth (inMessage); } break;
        case (MessageCode::kDelayDirection): { handleDelayDirection (inMessage); } break;
        case (MessageCode::kDelayVariance): { handleDelayVariance (inMessage); } break;
        case (MessageCode::kVelocityDepth): { handleVelocityDepth (inMessage); } break;
        case (MessageCode::kVelocityDirection): { handleVelocityDirection (inMessage); } break;
        case (MessageCode::kVelocityVariance): { handleVelocityVariance (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void PlayControlsComponent::handleToggleMode (const DataMessage* inMessage)
{
    if (mGlobalState.isEditMode()) { setVisible (false); }

    if (mGlobalState.isPlayMode())
    {
        setVisible (true);
        updateRecordButtons();
        updateTransposeButton();
        updateDelayControlImages();
        updateDelayVarianceImage();
        updateVelocityControlImages();
        updateVelocityVarianceImage();

        mDelayDepthSlider.setValue (mControlsState.getDelayDepth() * 100000);
        mDelayVarianceSlider.setValue (mControlsState.getDelayVariance() * 100000);
        mVelocityDepthSlider.setValue (mControlsState.getVelocityDepth() * 100000);
        mVelocityVarianceSlider.setValue (mControlsState.getVelocityVariance() * 100000);
    }
}

void PlayControlsComponent::handleIsRecording (const DataMessage* inMessage)
{
    updateRecordButtons();
}

void PlayControlsComponent::handleToggleRecord (const DataMessage* inMessage)
{
    updateRecordButtons();
}

void PlayControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    updateTransposeButton();
}

void PlayControlsComponent::handleDelayDepth (const DataMessage* inMessage)
{
    updateDelayControlImages();
}

void PlayControlsComponent::handleDelayDirection (const DataMessage* inMessage)
{
    updateDelayControlImages();
}

void PlayControlsComponent::handleDelayVariance (const DataMessage* inMessage)
{
    updateDelayVarianceImage();
}

void PlayControlsComponent::handleVelocityDepth (const DataMessage* inMessage)
{
    updateVelocityControlImages();
}

void PlayControlsComponent::handleVelocityDirection (const DataMessage* inMessage)
{
    updateVelocityControlImages();
}

void PlayControlsComponent::handleVelocityVariance (const DataMessage* inMessage)
{
    updateVelocityVarianceImage();
}

void PlayControlsComponent::updateRecordButtons()
{
    if (!mControlsState.isRecordOn())
    {
        mImages.setDrawableButtonImages (mRecordButton, "Record.svg");
    }
    else if (mMidiState.isRecording())
    {
        mImages.setDrawableButtonImages (mRecordButton, "RecordON.svg");
    }
    else
    {
        mImages.setDrawableButtonImages (mRecordButton, "RecordIN.svg");
    }

    if (mMidiState.isRecording())
    {
        mRecordedMidi.setButtonImage ("RecordedIN.svg");
    }
    else if (!mMidiState.isRecordedSequenceEmpty())
    {
        mRecordedMidi.setButtonImage ("RecordedON.svg");
    }
    else
    {
        mRecordedMidi.setButtonImage ("Recorded.svg");
    }
}

void PlayControlsComponent::updateTransposeButton()
{
    String buttonImage = mControlsState.isTransposeOn() ? "TransposeON.svg" : "Transpose.svg";
    mImages.setDrawableButtonImages (mTransposeButton, buttonImage);
}

void PlayControlsComponent::updateDelayControlImages()
{
    String depthImage = "Delay.svg";
    String directionImage = "Direction.svg";
    String delayDirection = mControlsState.getDelayDirection();

    if (mControlsState.getDelayDepth() == 0) { depthImage = "Delay.svg"; }
    else { depthImage = "DelayON.svg"; }

    if (mControlsState.getDelayDepth() == 0) { directionImage = "Direction.svg"; }
    else if (delayDirection == "LTR") { directionImage = "DirectionAB.svg"; }
    else if (delayDirection == "RTL") { directionImage = "DirectionBA.svg"; }
    else if (delayDirection == "LTR_RTL") { directionImage = "DirectionABBA.svg"; }
    else if (delayDirection == "RTL_LTR") { directionImage = "DirectionBAAB.svg"; }

    mImages.setDrawableButtonImages (mDelayDepthImage, depthImage);
    mImages.setDrawableButtonImages (mDelayDirectionButton, directionImage);
}

void PlayControlsComponent::updateDelayVarianceImage()
{
    String varianceImage = "Variance.svg";

    if (mControlsState.getDelayVariance() == 0) { varianceImage = "Variance.svg"; }
    else { varianceImage = "VarianceON.svg"; }

    mImages.setDrawableButtonImages (mDelayVarianceImage, varianceImage);
}

void PlayControlsComponent::updateVelocityControlImages()
{
    String depthImage = "Velocity.svg";
    String directionImage = "Direction.svg";
    String velocityDirection = mControlsState.getVelocityDirection();

    if (mControlsState.getVelocityDepth() == 0) { depthImage = "Velocity.svg"; }
    else { depthImage = "VelocityON.svg"; }

    if (mControlsState.getVelocityDepth() == 0) { directionImage = "Direction.svg"; }
    else if (velocityDirection == "HTS") { directionImage = "DirectionAB.svg"; }
    else if (velocityDirection == "STH") { directionImage = "DirectionBA.svg"; }
    else if (velocityDirection == "HTS_STH") { directionImage = "DirectionABBA.svg"; }
    else if (velocityDirection == "STH_HTS") { directionImage = "DirectionBAAB.svg"; }

    mImages.setDrawableButtonImages (mVelocityDepthImage, depthImage);
    mImages.setDrawableButtonImages (mVelocityDirectionButton, directionImage);
}

void PlayControlsComponent::updateVelocityVarianceImage()
{
    String varianceImage = "Variance.svg";

    if (mControlsState.getVelocityVariance() == 0) { varianceImage = "Variance.svg"; }
    else { varianceImage = "VarianceON.svg"; }

    mImages.setDrawableButtonImages (mVelocityVarianceImage, varianceImage);
}
