#include "ControlsState.h"

//==============================================================================
ControlsState::ControlsState()
{
}

ControlsState::~ControlsState()
{
}

//==============================================================================
bool ControlsState::isTransposeOff()
{
    return mTranspose == Transpose::Off;
}

bool ControlsState::isTransposeOn()
{
    return mTranspose == Transpose::On;
}

//==============================================================================
int ControlsState::getTransposeBase()
{
    return mTransposeBase;
}

bool ControlsState::isTransposeNote (const int inInputNote)
{
    return mTransposeBase <= inInputNote && inInputNote < (mTransposeBase + 25);
}

int ControlsState::getTransposedNote (const int inOutputNote, const int inCurrentlyOnTransposeNote)
{
    if (isTransposeOff() || inCurrentlyOnTransposeNote == -1) { return inOutputNote; }
    return inOutputNote + (inCurrentlyOnTransposeNote - mTransposeBase - 12);
}

//==============================================================================
void ControlsState::toggleTranspose()
{
    mTranspose = isTransposeOff() ? Transpose::On : Transpose::Off;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleTranspose;
    message->messageVar1 = mTransposeBase;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleMouseClickOnShiftLeft()
{
    if (mTransposeBase == 21 || isTransposeOff()) { return; }

    int prevTransposeBase = mTransposeBase;
    int nextTransposeBase = mTransposeBase - 1;

    mTransposeBase = nextTransposeBase;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTransposeBaseChanged;
    message->messageVar1 = prevTransposeBase;
    message->messageVar2 = nextTransposeBase;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleMouseClickOnShiftRight()
{
    if (mTransposeBase == 84 || isTransposeOff()) { return; }

    int prevTransposeBase = mTransposeBase;
    int nextTransposeBase = mTransposeBase + 1;

    mTransposeBase = nextTransposeBase;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTransposeBaseChanged;
    message->messageVar1 = prevTransposeBase;
    message->messageVar2 = nextTransposeBase;
    sendMessage (message, ListenerType::kSync);
}
