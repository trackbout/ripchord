#include "ControlsComponent.h"

//==============================================================================
ControlsComponent::ControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mControlsState (mMainProcess.getControlsState()),
    mMidiState (mMainProcess.getMidiState())
{
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");

    mShiftLeftButton.setTriggeredOnMouseDown (true);
    mTransposeButton.setTriggeredOnMouseDown (true);
    mShiftRightButton.setTriggeredOnMouseDown (true);

    mShiftLeftButton.onClick = [this]()
    {
        if (mMidiState.shouldPreventToggleTranspose()) { return; }
        mControlsState.handleMouseClickOnShiftLeft();
    };

    mTransposeButton.onClick = [this]()
    {
        if (mMidiState.shouldPreventToggleTranspose()) { return; }
        mControlsState.toggleTranspose();
    };

    mShiftRightButton.onClick = [this]()
    {
        if (mMidiState.shouldPreventToggleTranspose()) { return; }
        mControlsState.handleMouseClickOnShiftRight();
    };

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
    if (mControlsState.isTransposeEnabled()) { mTransposeButton.setImages (mImages.getDrawable ("TransposeENABLED.svg")); }
    if (mControlsState.isTransposeLatched()) { mTransposeButton.setImages (mImages.getDrawable ("TransposeLATCHED.svg")); }
}
