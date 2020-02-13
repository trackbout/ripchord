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
float ControlsState::getDelayDepth()
{
    return mDelayDepth / 100000.f;
}

float ControlsState::getDelayVariance()
{
    return mDelayVariance / 100000.f;
}

String ControlsState::getDelayDirection()
{
    return mDelayDirection;
}

void ControlsState::cycleDelayDirection()
{
    if (mDelayDirection == "LTR") { mDelayDirection = "RTL"; }
    else if (mDelayDirection == "RTL") { mDelayDirection = "LTR_RTL"; }
    else if (mDelayDirection == "LTR_RTL") { mDelayDirection = "RTL_LTR"; }
    else if (mDelayDirection == "RTL_LTR") { mDelayDirection = "LTR"; }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kDelayDirection;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleDelayDepthSlider (int inDelayDepth)
{
    mDelayDepth = inDelayDepth;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kDelayDepth;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleDelayVarianceSlider (int inDelayVariance)
{
    mDelayVariance = inDelayVariance;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kDelayVariance;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
float ControlsState::getVelocityDepth()
{
    return mVelocityDepth / 100000.f;
}

float ControlsState::getVelocityVariance()
{
    return mVelocityVariance / 100000.f;
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
juce::Array<int> ControlsState::getSortedChordNotes (juce::Array<int> inChordNotes)
{
    if (mDelayVariance >= MIN_DELAY_VARIANCE && mDelayDepth < MIN_DELAY_DEPTH)
    {
        std::default_random_engine randomize (std::random_device{}());
        std::shuffle (inChordNotes.begin(), inChordNotes.end(), randomize);
    }
    else
    {
        inChordNotes.sort (mForward);
    }

    return inChordNotes;
}

//==============================================================================
XmlElement* ControlsState::exportControlsStateXml()
{
    XmlElement* controlsStateXml = new XmlElement ("ControlsState");

    controlsStateXml->setAttribute ("transpose", isTransposeOn());
    controlsStateXml->setAttribute ("transposeBase", mTransposeBase);
    controlsStateXml->setAttribute ("activeTransposeNote", mActiveTransposeNote);

    controlsStateXml->setAttribute ("delayDepth", mDelayDepth);
    controlsStateXml->setAttribute ("delayVariance", mDelayVariance);
    controlsStateXml->setAttribute ("delayDirection", mDelayDirection);

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

    mDelayDepth = inControlsStateXml->getIntAttribute ("delayDepth");
    mDelayVariance = inControlsStateXml->getIntAttribute ("delayVariance");
    mDelayDirection = inControlsStateXml->getStringAttribute ("delayDirection");

    mVelocityDepth = inControlsStateXml->getIntAttribute ("velocityDepth");
    mVelocityVariance = inControlsStateXml->getIntAttribute ("velocityVariance");
    mVelocityDirection = inControlsStateXml->getStringAttribute ("velocityDirection");
}
