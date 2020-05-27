#pragma once

const float MIN_VELOCITY = 0.01f;
const float MAX_VELOCITY = 1.0f;

const float MIN_DELAY_DEPTH = 0.01f;
const float MAX_DELAY_DEPTH_MS = 100;
const float MIN_DELAY_VARIANCE = 0.01f;

//==============================================================================
struct Origin
{
    juce::Array<int> triggers;
};

struct NoteEvent {
    int channel;
    int samplePosition;
    float velocity;
    int inputNote;
    int outputNote;
    int delayInMS;

    NoteEvent
    (
        int& inChannel,
        int& inSamplePosition,
        float& inVelocity,
        int& inInputNote,
        int& inOutputNote
    )
    :   channel (inChannel),
        samplePosition (inSamplePosition),
        velocity (inVelocity),
        inputNote (inInputNote),
        outputNote (inOutputNote)
    {
    }
};
