#pragma once

const int DOUBLE_TRIGGER_WEIGHT = 1000;

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
