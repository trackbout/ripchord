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

    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg", "", "ShiftLeftON.svg", "");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg", "", "ShiftRightON.svg", "");

    mShiftLeftButton.setTriggeredOnMouseDown (true);
    mTransposeButton.setTriggeredOnMouseDown (true);
    mShiftRightButton.setTriggeredOnMouseDown (true);

    mShiftLeftButton.onClick = [this]()
    {
        if (isTransposeArrowDisabled()) { return; }
        mControlsState.handleMouseClickOnShiftLeft();
    };

    mTransposeButton.onClick = [this]()
    {
        if (isTransposeToggleDisabled()) { return; }
        if (mMidiState.getCurrentlyOnTransposeNote() > 0) { mMidiState.setCurrentlyOnTransposeNote (-1); }
        mControlsState.toggleTranspose();
    };

    mShiftRightButton.onClick = [this]()
    {
        if (isTransposeArrowDisabled()) { return; }
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
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void ControlsComponent::handleToggleMode (const DataMessage* inMessage)
{
    if (mGlobalState.isPlayMode()) { return; }
    if (mMidiState.getCurrentlyOnTransposeNote() > 0) { mMidiState.setCurrentlyOnTransposeNote (-1); }
    if (mControlsState.isTransposeOn()) { mControlsState.toggleTranspose(); }
}

void ControlsComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    String svgPath = mControlsState.isTransposeOff() ? "Transpose.svg" : "TransposeON.svg";
    mImages.setDrawableButtonImages (mTransposeButton, svgPath);
}

bool ControlsComponent::isTransposeArrowDisabled()
{
    if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return true; }
    if (mMidiState.getCurrentlyOnTransposeNote() > 0) { return true; }
    if (mGlobalState.isEditMode()) { return true; }
    return false;
}

bool ControlsComponent::isTransposeToggleDisabled()
{
    if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return true; }
    if (mGlobalState.isEditMode()) { return true; }
    return false;
}
