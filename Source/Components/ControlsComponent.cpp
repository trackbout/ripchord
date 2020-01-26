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

    mImages.setDrawableButtonImages (mVelocityDepth, "Velocity.svg");
    mImages.setDrawableButtonImages (mVelocityAlternate, "Alternate.svg");
    mImages.setDrawableButtonImages (mVelocityVariance, "Variance.svg");

    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");

    mImages.setDrawableButtonImages (mTimingVariance, "Variance.svg");
    mImages.setDrawableButtonImages (mTimingAlternate, "Alternate.svg");
    mImages.setDrawableButtonImages (mTimingDepth, "Timing.svg");

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

    addChildComponent (mVelocityDepth);
    addChildComponent (mVelocityAlternate);
    addChildComponent (mVelocityVariance);

    addAndMakeVisible (mShiftLeftButton);
    addAndMakeVisible (mTransposeButton);
    addAndMakeVisible (mShiftRightButton);

    addChildComponent (mTimingVariance);
    addChildComponent (mTimingAlternate);
    addChildComponent (mTimingDepth);
}

ControlsComponent::~ControlsComponent()
{
}

//==============================================================================
void ControlsComponent::resized()
{
    mVelocityDepth.setBounds (VELOCITY_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityAlternate.setBounds (VELOCITY_ALTERNATE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mVelocityVariance.setBounds (VELOCITY_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mShiftLeftButton.setBounds (SHIFT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTransposeButton.setBounds (TRANSPOSE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mShiftRightButton.setBounds (SHIFT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);

    mTimingVariance.setBounds (TIMING_VARIANCE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingAlternate.setBounds (TIMING_ALTERNATE_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTimingDepth.setBounds (TIMING_DEPTH_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
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
    if (mGlobalState.isPlayMode()) { return; }
    if (mControlsState.isTransposeOn()) { mControlsState.toggleTranspose(); }
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
