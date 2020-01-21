#include "ControlsState.h"

//==============================================================================
ControlsState::ControlsState()
{
}

ControlsState::~ControlsState()
{
}

//==============================================================================
void ControlsState::toggleTranspose()
{
    switch (mTranspose)
    {
        case (Transpose::Off): { mTranspose = Transpose::On; } break;
        case (Transpose::On): { mTranspose = Transpose::Locked; } break;
        case (Transpose::Locked): { mTranspose = Transpose::Off; } break;
    };

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleTranspose;
    sendMessage (message, ListenerType::kSync);
}

bool ControlsState::isTransposeOff()
{
    return mTranspose == Transpose::Off;
}

bool ControlsState::isTransposeOn()
{
    return mTranspose == Transpose::On;
}

bool ControlsState::isTransposeLocked()
{
    return mTranspose == Transpose::Locked;
}
