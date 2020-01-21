#include "ControlsComponent.h"

//==============================================================================
ControlsComponent::ControlsComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess)
{
}

ControlsComponent::~ControlsComponent()
{
}

//==============================================================================
void ControlsComponent::paint (Graphics& inGraphics)
{

}

void ControlsComponent::resized()
{

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
