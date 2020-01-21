#include "ControlsComponent.h"

//==============================================================================
ControlsComponent::ControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mControlsState (mMainProcess.getControlsState())
{
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mShiftLeftButton.setImages (mImages.getDrawable ("ShiftLeft.svg"));
    mTransposeButton.setImages (mImages.getDrawable ("Transpose.svg"));
    mShiftRightButton.setImages (mImages.getDrawable ("ShiftRight.svg"));

    mTransposeButton.setTriggeredOnMouseDown (true);
    mTransposeButton.onClick = [this]() { mControlsState.toggleTranspose(); };

    addAndMakeVisible (mShiftLeftButton);
    addAndMakeVisible (mTransposeButton);
    addAndMakeVisible (mShiftRightButton);
}

ControlsComponent::~ControlsComponent()
{
}

//==============================================================================
void ControlsComponent::resized()
{
    mShiftLeftButton.setBounds (SHIFT_LEFT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mTransposeButton.setBounds (TRANSPOSE_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
    mShiftRightButton.setBounds (SHIFT_RIGHT_BUTTON_X, SPACE, ITEM_HEIGHT, ITEM_HEIGHT);
}

//==============================================================================
void ControlsComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void ControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    if (mControlsState.isTransposeOff()) { mTransposeButton.setImages (mImages.getDrawable ("Transpose.svg")); }
    if (mControlsState.isTransposeOn()) { mTransposeButton.setImages (mImages.getDrawable ("TransposeON.svg")); }
    if (mControlsState.isTransposeLocked()) { mTransposeButton.setImages (mImages.getDrawable ("TransposeLOCK.svg")); }
}
