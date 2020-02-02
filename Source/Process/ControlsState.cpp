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
int ControlsState::getTimingDepth()
{
    return mTimingDepth;
}

int ControlsState::getTimingVariance()
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

void ControlsState::handleTimingDepthSlider (int inTimingDepth)
{
    mTimingDepth = inTimingDepth;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingDepth;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleTimingVarianceSlider (int inTimingVariance)
{
    mTimingVariance = inTimingVariance;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTimingVariance;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
int ControlsState::getVelocityDepth()
{
    return mVelocityDepth;
}

int ControlsState::getVelocityVariance()
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

void ControlsState::handleVelocityDepthSlider (int inVelocityDepth)
{
    mVelocityDepth = inVelocityDepth;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityDepth;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleVelocityVarianceSlider (int inVelocityVariance)
{
    mVelocityVariance = inVelocityVariance;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kVelocityVariance;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
XmlElement* ControlsState::exportControlsStateXml()
{
    XmlElement* controlsStateXml = new XmlElement ("ControlsState");

    controlsStateXml->setAttribute ("transpose", isTransposeOn());
    controlsStateXml->setAttribute ("transposeBase", mTransposeBase);
    controlsStateXml->setAttribute ("activeTransposeNote", mActiveTransposeNote);

    controlsStateXml->setAttribute ("timingDepth", mTimingDepth);
    controlsStateXml->setAttribute ("timingVariance", mTimingVariance);
    controlsStateXml->setAttribute ("timingDirection", mTimingDirection);

    controlsStateXml->setAttribute ("velocityDepth", mVelocityDepth);
    controlsStateXml->setAttribute ("velocityVariance", mVelocityVariance);
    controlsStateXml->setAttribute ("velocityDirection", mVelocityDirection);

    return controlsStateXml;
}

void ControlsState::importControlsStateXml (XmlElement* inControlsStateXml)
{
    mTranspose = inControlsStateXml->getBoolAttribute ("transpose") ? Transpose::On : Transpose::Off;
    mTransposeBase = inControlsStateXml->getIntAttribute ("transposeBase");
    mActiveTransposeNote = inControlsStateXml->getIntAttribute ("activeTransposeNote");

    mTimingDepth = inControlsStateXml->getIntAttribute ("timingDepth");
    mTimingVariance = inControlsStateXml->getIntAttribute ("timingVariance");
    mTimingDirection = inControlsStateXml->getStringAttribute ("timingDirection");

    mVelocityDepth = inControlsStateXml->getIntAttribute ("velocityDepth");
    mVelocityVariance = inControlsStateXml->getIntAttribute ("velocityVariance");
    mVelocityDirection = inControlsStateXml->getStringAttribute ("velocityDirection");
}
