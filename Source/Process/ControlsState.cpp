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
    mActiveTransposeNote = mActiveTransposeNote < 0 ? -1 : mActiveTransposeNote - 1;

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
    mActiveTransposeNote = mActiveTransposeNote < 0 ? -1 : mActiveTransposeNote + 1;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTransposeBase;
    message->messageVar1 = prevTransposeBase;
    message->messageVar2 = nextTransposeBase;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
float ControlsState::getTimingDepth()
{
    return mTimingDepth;
}

float ControlsState::getTimingVariance()
{
    return mTimingVariance;
}

String ControlsState::getTimingDirection()
{
    return mTimingDirection;
}

void ControlsState::cycleTimingDirection()
{
    if (mTimingDirection == "LTR") { mTimingDirection = "RTL"; }
    else if (mTimingDirection == "RTL") { mTimingDirection = "LTR_RTL"; }
    else if (mTimingDirection == "LTR_RTL") { mTimingDirection = "RTL_LTR"; }
    else if (mTimingDirection == "RTL_LTR") { mTimingDirection = "LTR"; }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingDirection;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleTimingDepthSlider (float inTimingDepth)
{
    mTimingDepth = inTimingDepth;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingDepth;
    message->messageVar1 = inTimingDepth;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleTimingVarianceSlider (float inTimingVariance)
{
    mTimingVariance = inTimingVariance;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingVariance;
    message->messageVar1 = inTimingVariance;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
float ControlsState::getVelocityDepth()
{
    return mVelocityDepth;
}

float ControlsState::getVelocityVariance()
{
    return mVelocityVariance;
}

String ControlsState::getVelocityDirection()
{
    return mVelocityDirection;
}

void ControlsState::cycleVelocityDirection()
{
    if (mVelocityDirection == "HTS") { mVelocityDirection = "STH"; }
    else if (mVelocityDirection == "STH") { mVelocityDirection = "HTS_STH"; }
    else if (mVelocityDirection == "HTS_STH") { mVelocityDirection = "STH_HTS"; }
    else if (mVelocityDirection == "STH_HTS") { mVelocityDirection = "HTS"; }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityDirection;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleVelocityDepthSlider (float inVelocityDepth)
{
    mVelocityDepth = inVelocityDepth;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityDepth;
    message->messageVar1 = inVelocityDepth;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleVelocityVarianceSlider (float inVelocityVariance)
{
    mVelocityVariance = inVelocityVariance;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityVariance;
    message->messageVar1 = inVelocityVariance;
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
