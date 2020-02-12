#pragma once

const float MIN_DELAY_DEPTH = 0.01;
const float MAX_DELAY_DEPTH_MS = 100;
const float MIN_DELAY_VARIANCE = 0.01;
const float MIN_DELAY_VARIANCE_MS = 100;

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
