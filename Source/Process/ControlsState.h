#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class ControlsState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    ControlsState();
    ~ControlsState();

    //==============================================================================
    enum Transpose { On, Off };
    enum TimingDirection { LTR, RTL, LTR_RTL, RTL_LTR };
    enum VelocityDirection { HTS, STH, HTS_STH, STH_HTS };

    //==============================================================================
    bool isTransposeOn();
    bool isTransposeOff();

    //==============================================================================
    int getTransposeBase();
    int getActiveTransposeNote();
    void setActiveTransposeNote (const int inputNote);

    //==============================================================================
    bool isTransposeNote (const int inputNote);
    int getTransposedNote (const int outputNote, const int activeTransposeNote);

    //==============================================================================
    void toggleTranspose();
    void handleMouseClickOnShiftLeft();
    void handleMouseClickOnShiftRight();

    //==============================================================================
    void cycleTimingDirection();
    void handleTimingDepthSlider (float timingDepth);
    void handleTimingVarianceSlider (float timingVariance);

    //==============================================================================
    void cycleVelocityDirection();
    void handleVelocityDepthSlider (float velocityDepth);
    void handleVelocityVarianceSlider (float velocityVariance);

    //==============================================================================
    XmlElement* exportControlsStateXml();
    void importControlsStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    Transpose mTranspose = Transpose::Off;
    TimingDirection mTimingDirection = TimingDirection::LTR;
    VelocityDirection mVelocityDirection = VelocityDirection::HTS;

    int mTransposeBase = 21;
    int mActiveTransposeNote = -1;

    float mTimingDepth = 0.f;
    float mTimingVariance = 0.f;

    float mVelocityDepth = 0.f;
    float mVelocityVariance = 0.f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
