#include "ControlsState.h"

//==============================================================================
ControlsState::ControlsState()
{
}

ControlsState::~ControlsState()
{
}

//==============================================================================
bool ControlsState::isTransposeOn()
{
    return mTranspose == Transpose::On;
}

bool ControlsState::isTransposeOff()
{
    return mTranspose == Transpose::Off;
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
bool ControlsState::isTimingAlternateOn()
{
    return mTimingAlternate == TimingAlternate::On;
}

bool ControlsState::isTimingAlternateOff()
{
    return mTimingAlternate == TimingAlternate::Off;
}

void ControlsState::toggleTimingAlternate()
{
    mTimingAlternate = isTimingAlternateOff() ? TimingAlternate::On : TimingAlternate::Off;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingAlternate;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
bool ControlsState::isVelocityAlternateOn()
{
    return mVelocityAlternate == VelocityAlternate::On;
}

bool ControlsState::isVelocityAlternateOff()
{
    return mVelocityAlternate == VelocityAlternate::Off;
}

void ControlsState::toggleVelocityAlternate()
{
    mVelocityAlternate = isVelocityAlternateOff() ? VelocityAlternate::On : VelocityAlternate::Off;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityAlternate;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
XmlElement* ControlsState::exportControlsStateXml()
{
    XmlElement* controlsStateXml = new XmlElement ("ControlsState");
    controlsStateXml->setAttribute ("transposeBase", mTransposeBase);
    controlsStateXml->setAttribute ("activeTransposeNote", mActiveTransposeNote);
    controlsStateXml->setAttribute ("isTransposeOn", isTransposeOn());
    controlsStateXml->setAttribute ("isTimingAlternateOn", isTimingAlternateOn());
    controlsStateXml->setAttribute ("isVelocityAlternateOn", isVelocityAlternateOn());
    return controlsStateXml;
}

void ControlsState::importControlsStateXml (XmlElement* inControlsStateXml)
{
    bool isTransposeOn = inControlsStateXml->getBoolAttribute ("isTransposeOn");
    bool isTimingAlternateOn = inControlsStateXml->getBoolAttribute ("isTimingAlternateOn");
    bool isVelocityAlternateOn = inControlsStateXml->getBoolAttribute ("isVelocityAlternateOn");

    mTranspose = isTransposeOn ? Transpose::On : Transpose::Off;
    mTimingAlternate = isTimingAlternateOn ? TimingAlternate::On : TimingAlternate::Off;
    mVelocityAlternate = isVelocityAlternateOn ? VelocityAlternate::On : VelocityAlternate::Off;

    mTransposeBase = inControlsStateXml->getIntAttribute ("transposeBase");
    mActiveTransposeNote = inControlsStateXml->getIntAttribute ("activeTransposeNote");
}
