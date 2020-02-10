#pragma once

const float MIN_DELAY_DEPTH = 0.001;
const float MIN_DELAY_VARIANCE = 0.001;

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
    bool isNoteOn;
    int64 timeToSend;

    NoteEvent
    (
        int& inChannel,
        int& inSampleNumber,
        float& inVelocity,
        int& inInputNote,
        int& inOutputNote,
        bool& inIsNoteOn
    )
    :   channel (inChannel),
        sampleNumber (inSampleNumber),
        velocity (inVelocity),
        inputNote (inInputNote),
        outputNote (inOutputNote),
        isNoteOn (inIsNoteOn)
    {
    }
};
