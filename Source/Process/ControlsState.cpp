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

int ControlsState::getActiveTransposeNote()
{
    return mActiveTransposeNote;
}

void ControlsState::setActiveTransposeNote (const int inInputNote)
{
    const int prevActiveTransposeNote = mActiveTransposeNote;
    const int nextActiveTransposeNote = inInputNote;

    mActiveTransposeNote = nextActiveTransposeNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kActiveTransposeNote;
    message->messageVar1 = prevActiveTransposeNote;
    message->messageVar2 = nextActiveTransposeNote;
    sendMessage (message, ListenerType::kAsync);
}

//==============================================================================
bool ControlsState::isTransposeNote (const int inInputNote)
{
    return mTransposeBase <= inInputNote && inInputNote < (mTransposeBase + 25);
}

int ControlsState::getTransposedNote (const int inOutputNote, const int inActiveTransposeNote)
{
    if (isTransposeOff() || inActiveTransposeNote == -1) { return inOutputNote; }
    return inOutputNote + (inActiveTransposeNote - mTransposeBase - 12);
}

//==============================================================================
void ControlsState::toggleTranspose()
{
    mTranspose = isTransposeOff() ? Transpose::On : Transpose::Off;
    if (mActiveTransposeNote > 0) { mActiveTransposeNote = -1; }

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
    message->messageCode = MessageCode::kTransposeBase;
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
    message->messageCode = MessageCode::kTransposeBase;
    message->messageVar1 = prevTransposeBase;
    message->messageVar2 = nextTransposeBase;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
XmlElement* ControlsState::exportControlsStateXml()
{
    XmlElement* controlsStateXml = new XmlElement ("ControlsState");
    controlsStateXml->setAttribute ("transposeBase", mTransposeBase);
    controlsStateXml->setAttribute ("activeTransposeNote", mActiveTransposeNote);
    controlsStateXml->setAttribute ("isTransposeOn", isTransposeOn());
    return controlsStateXml;
}

void ControlsState::importControlsStateXml (XmlElement* inControlsStateXml)
{
    mTransposeBase = inControlsStateXml->getIntAttribute ("transposeBase");
    mActiveTransposeNote = inControlsStateXml->getIntAttribute ("activeTransposeNote");
    mTranspose = inControlsStateXml->getBoolAttribute ("isTransposeOn") ? Transpose::On : Transpose::Off;
}
