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
    int sampleNumber;
    float velocity;
    int inputNote;
    int outputNote;
    int64 timeToSend;

    NoteEvent
    (
        int& inChannel,
        int& inSampleNumber,
        float& inVelocity,
        int& inInputNote,
        int& inOutputNote
    )
    :   channel (inChannel),
        sampleNumber (inSampleNumber),
        velocity (inVelocity),
        inputNote (inInputNote),
        outputNote (inOutputNote)
    {
    }
};
