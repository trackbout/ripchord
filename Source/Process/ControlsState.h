#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"
#include "Sorting.h"
#include "Midi.h"
#include <algorithm>
#include <random>

//==============================================================================
class ControlsState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    ControlsState();
    ~ControlsState();

    //==============================================================================
    bool isRecordOn();
    void toggleRecord();

    //==============================================================================
    bool isTransposeOn();
    void toggleTranspose();

    //==============================================================================
    int getTransposeBase();
    int getActiveTransposeNote();
    void setActiveTransposeNote (const int inputNote);

    //==============================================================================
    bool isTransposeNote (const int inputNote);
    int getTransposedNote (const int outputNote, const int activeTransposeNote);

    //==============================================================================
    void handleClickShiftLeft();
    void handleClickShiftRight();

    //==============================================================================
    float getDelayDepth();
    float getDelayVariance();
    String getDelayDirection();
    void cycleDelayDirection();
    void handleDelayDepthSlider (int delayDepth);
    void handleDelayVarianceSlider (int delayVariance);

    //==============================================================================
    float getVelocityDepth();
    float getVelocityVariance();
    String getVelocityDirection();
    void cycleVelocityDirection();
    void handleVelocityDepthSlider (int velocityDepth);
    void handleVelocityVarianceSlider (int velocityVariance);

    //==============================================================================
    NoteEvent setVelocity (NoteEvent noteEvent, int index, int count);
    juce::Array<int> getSortedChordNotes (int inputNote, juce::Array<int> chordNotes);

    //==============================================================================
    XmlElement* exportControlsStateXml();
    void importControlsStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    Forward mForward;
    Reverse mReverse;

    bool mIsRecordOn = false;
    bool mIsTransposeOn = false;

    int mTransposeBase = 21;
    int mActiveTransposeNote = -1;

    int mDelayDepth = 0;
    int mDelayVariance = 0;
    int mLastDelayNote = 0;
    String mDelayDirection = "LTR";

    int mVelocityDepth = 0;
    int mVelocityVariance = 0;
    int mLastVelocityNote = 0;
    String mVelocityDirection = "HTS";

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
