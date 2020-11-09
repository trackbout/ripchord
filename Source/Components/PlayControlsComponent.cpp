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
    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");
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
        if (mMidiState.isPlaying()) { return; }
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
        case (MessageCode::kIsPlaying): { handleIsPlaying (inMessage); } break;
        case (MessageCode::kToggleRecord): { handleToggleRecord (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        case (MessageCode::kDelayDepth): { handleDelayDepth (inMessage); } break;
        case (MessageCode::kDelayDirection): { handleDelayDirection (inMessage); } break;
        case (MessageCode::kVelocityDepth): { handleVelocityDepth (inMessage); } break;
        case (MessageCode::kVelocityDirection): { handleVelocityDirection (inMessage); } break;
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
        updateRecordButton();
        updateRecordedButton();
        updateTransposeButton();
        updateDelayDirectionButton();
        updateVelocityDirectionButton();
        mDelayDepthSlider.setValue (mControlsState.getDelayDepth() * 100000);
        mDelayVarianceSlider.setValue (mControlsState.getDelayVariance() * 100000);
        mVelocityDepthSlider.setValue (mControlsState.getVelocityDepth() * 100000);
        mVelocityVarianceSlider.setValue (mControlsState.getVelocityVariance() * 100000);
    }
}

void PlayControlsComponent::handleIsPlaying (const DataMessage* inMessage)
{
    updateRecordButton();
    updateRecordedButton();
}

void PlayControlsComponent::handleToggleRecord (const DataMessage* inMessage)
{
    updateRecordButton();
}

void PlayControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    updateTransposeButton();
}

void PlayControlsComponent::handleDelayDepth (const DataMessage* inMessage)
{
    updateDelayDirectionButton();
}

void PlayControlsComponent::handleDelayDirection (const DataMessage* inMessage)
{
    updateDelayDirectionButton();
}

void PlayControlsComponent::handleVelocityDepth (const DataMessage* inMessage)
{
    updateVelocityDirectionButton();
}

void PlayControlsComponent::handleVelocityDirection (const DataMessage* inMessage)
{
    updateVelocityDirectionButton();
}

void PlayControlsComponent::updateRecordButton()
{
    if (mControlsState.isRecordOff())
    {
        mImages.setDrawableButtonImages (mRecordButton, "Record.svg");
    }
    else if (mMidiState.isPlaying())
    {
        mImages.setDrawableButtonImages (mRecordButton, "RecordON.svg");
    }
    else
    {
        mImages.setDrawableButtonImages (mRecordButton, "RecordIN.svg");
    }
}

void PlayControlsComponent::updateRecordedButton()
{
    if (mControlsState.isRecordIn() && mMidiState.isPlaying())
    {
        mRecordedMidi.setButtonImage ("RecordedIN.svg");
    }
    else
    {
        mRecordedMidi.setButtonImage ("Recorded.svg");
    }
}

void PlayControlsComponent::updateTransposeButton()
{
    String buttonImage = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
    mImages.setDrawableButtonImages (mTransposeButton, buttonImage);
}

void PlayControlsComponent::updateDelayDirectionButton()
{
    String buttonImage = "Direction.svg";
    String delayDirection = mControlsState.getDelayDirection();

    if (mControlsState.getDelayDepth() == 0) { buttonImage = "Direction.svg"; }
    else if (delayDirection == "LTR") { buttonImage = "DirectionAB.svg"; }
    else if (delayDirection == "RTL") { buttonImage = "DirectionBA.svg"; }
    else if (delayDirection == "LTR_RTL") { buttonImage = "DirectionABBA.svg"; }
    else if (delayDirection == "RTL_LTR") { buttonImage = "DirectionBAAB.svg"; }

    mImages.setDrawableButtonImages (mDelayDirectionButton, buttonImage);
}

void PlayControlsComponent::updateVelocityDirectionButton()
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
