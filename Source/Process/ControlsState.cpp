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
void ControlsState::cycleTimingDirection()
{
    switch (mTimingDirection)
    {
        case (TimingDirection::LTR): { mTimingDirection = TimingDirection::RTL; } break;
        case (TimingDirection::RTL): { mTimingDirection = TimingDirection::LTR_RTL; } break;
        case (TimingDirection::LTR_RTL): { mTimingDirection = TimingDirection::RTL_LTR; } break;
        case (TimingDirection::RTL_LTR): { mTimingDirection = TimingDirection::LTR; } break;
        default: { } break;
    };

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingDirection;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
void ControlsState::cycleVelocityDirection()
{
    switch (mVelocityDirection)
    {
        case (VelocityDirection::HTS): { mVelocityDirection = VelocityDirection::STH; } break;
        case (VelocityDirection::STH): { mVelocityDirection = VelocityDirection::HTS_STH; } break;
        case (VelocityDirection::HTS_STH): { mVelocityDirection = VelocityDirection::STH_HTS; } break;
        case (VelocityDirection::STH_HTS): { mVelocityDirection = VelocityDirection::HTS; } break;
        default: { } break;
    };

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityDirection;
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
    bool isTransposeOn = inControlsStateXml->getBoolAttribute ("isTransposeOn");
    mTranspose = isTransposeOn ? Transpose::On : Transpose::Off;
    mTransposeBase = inControlsStateXml->getIntAttribute ("transposeBase");
    mActiveTransposeNote = inControlsStateXml->getIntAttribute ("activeTransposeNote");
}
