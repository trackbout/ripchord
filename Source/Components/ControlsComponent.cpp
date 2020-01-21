#include "ControlsComponent.h"

//==============================================================================
ControlsComponent::ControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess)
{
    mImages.setDrawableButtonImages (mShiftLeftButton, "ShiftLeft.svg");
    mImages.setDrawableButtonImages (mTransposeButton, "Transpose.svg");
    mImages.setDrawableButtonImages (mShiftRightButton, "ShiftRight.svg");

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
        case (MessageCode::kToggleMode): { DBG ("YOLO"); } break;
        default: { } break;
    };
}
