#include "ControlsState.h"

//==============================================================================
ControlsState::ControlsState()
{
}

ControlsState::~ControlsState()
{
}

//==============================================================================
bool ControlsState::isRecordIn()
{
    return mRecord == Record::RecordIn;
}

bool ControlsState::isRecordOn()
{
    return mRecord == Record::RecordOn;
}

bool ControlsState::isRecordOff()
{
    return mRecord == Record::RecordOff;
}

//==============================================================================
bool ControlsState::isRecordedIn()
{
    return mRecorded == Recorded::RecordedIn;
}

bool ControlsState::isRecordedOn()
{
    return mRecorded == Recorded::RecordedOn;
}

bool ControlsState::isRecordedOff()
{
    return mRecorded == Recorded::RecordedOff;
}

//==============================================================================
void ControlsState::toggleRecord()
{
    mRecord = isRecordOff() ? Record::RecordIn : Record::RecordOff;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleRecord;
    sendMessage (message, ListenerType::kSync);
}

//==============================================================================
bool ControlsState::isTransposeOn()
{
    return mTranspose == Transpose::TransposeOn;
}

bool ControlsState::isTransposeOff()
{
    return mTranspose == Transpose::TransposeOff;
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
    mTranspose = isTransposeOff() ? Transpose::TransposeOn : Transpose::TransposeOff;
    if (mActiveTransposeNote > 0) { mActiveTransposeNote = -1; }

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleTranspose;
    message->messageVar1 = mTransposeBase;
    sendMessage (message, ListenerType::kSync);
}

void ControlsState::handleMouseDownOnShiftLeft()
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

void ControlsState::handleMouseDownOnShiftRight()
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
NoteEvent ControlsState::setVelocity (NoteEvent inNoteEvent, int inIndex, int inCount)
{
    float velocityDepth = getVelocityDepth();
    float velocityVariance = getVelocityVariance();
    if (velocityDepth == 0 && velocityVariance == 0) { return inNoteEvent; }

    float velocity = inNoteEvent.velocity;
    float headroom = MAX_VELOCITY - inNoteEvent.velocity;
    float variance = ((rand() % 20 - 10) / 10.0f) * (velocityVariance / 4.0f);
    float baseVelocity = velocityDepth < headroom ? inNoteEvent.velocity : MAX_VELOCITY - velocityDepth;

    if (mVelocityDirection == "HTS")
    {
        velocity = baseVelocity + ((abs (inIndex - inCount)) * (velocityDepth / inCount));
    }

    if (mVelocityDirection == "STH")
    {
        velocity = baseVelocity + ((inIndex + 1) * (velocityDepth / inCount));
    }

    if (mVelocityDirection == "HTS_STH")
    {
        if (inNoteEvent.inputNote == mLastVelocityNote)
        {
            velocity = baseVelocity + ((inIndex + 1) * (velocityDepth / inCount));
            if ((inIndex + 1) == inCount) { mLastVelocityNote = 0; }
        }
        else
        {
            velocity = baseVelocity + ((abs (inIndex - inCount)) * (velocityDepth / inCount));
            if ((inIndex + 1) == inCount) { mLastVelocityNote = inNoteEvent.inputNote; }
        }
    }

    if (mVelocityDirection == "STH_HTS")
    {
        if (inNoteEvent.inputNote == mLastVelocityNote)
        {
            velocity = baseVelocity + ((abs (inIndex - inCount)) * (velocityDepth / inCount));
            if ((inIndex + 1) == inCount) { mLastVelocityNote = 0; }
        }
        else
        {
            velocity = baseVelocity + ((inIndex + 1) * (velocityDepth / inCount));
            if ((inIndex + 1) == inCount) { mLastVelocityNote = inNoteEvent.inputNote; }
        }
    }

    inNoteEvent.velocity = std::max (MIN_VELOCITY, std::min ((velocity + variance), MAX_VELOCITY));
    return inNoteEvent;
}

juce::Array<int> ControlsState::getSortedChordNotes (int inInputNote, juce::Array<int> inChordNotes)
{
    if (mDelayVariance >= MIN_DELAY_VARIANCE && mDelayDepth < MIN_DELAY_DEPTH)
    {
        std::default_random_engine randomize (std::random_device{}());
        std::shuffle (inChordNotes.begin(), inChordNotes.end(), randomize);
        return inChordNotes;
    }

    if (mDelayDirection == "LTR") { inChordNotes.sort (mForward); }
    if (mDelayDirection == "RTL") { inChordNotes.sort (mReverse); }

    if (mDelayDirection == "LTR_RTL")
    {
        if (inInputNote == mLastDelayNote)
        {
            inChordNotes.sort (mReverse);
            mLastDelayNote = 0;
        }
        else
        {
            inChordNotes.sort (mForward);
            mLastDelayNote = inInputNote;
        }
    }

    if (mDelayDirection == "RTL_LTR")
    {
        if (inInputNote == mLastDelayNote)
        {
            inChordNotes.sort (mForward);
            mLastDelayNote = 0;
        }
        else
        {
            inChordNotes.sort (mReverse);
            mLastDelayNote = inInputNote;
        }
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
    mTranspose = inControlsStateXml->getBoolAttribute ("transpose") ? Transpose::TransposeOn : Transpose::TransposeOff;
    mTransposeBase = inControlsStateXml->getIntAttribute ("transposeBase");
    mActiveTransposeNote = inControlsStateXml->getIntAttribute ("activeTransposeNote");

    mDelayDepth = inControlsStateXml->getIntAttribute ("delayDepth");
    mDelayVariance = inControlsStateXml->getIntAttribute ("delayVariance");
    mDelayDirection = inControlsStateXml->getStringAttribute ("delayDirection");

    mVelocityDepth = inControlsStateXml->getIntAttribute ("velocityDepth");
    mVelocityVariance = inControlsStateXml->getIntAttribute ("velocityVariance");
    mVelocityDirection = inControlsStateXml->getStringAttribute ("velocityDirection");
}
