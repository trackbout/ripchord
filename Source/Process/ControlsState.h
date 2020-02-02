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
    float getTimingDepth();
    float getTimingVariance();
    String getTimingDirection();
    void cycleTimingDirection();
    void handleTimingDepthSlider (float timingDepth);
    void handleTimingVarianceSlider (float timingVariance);

    //==============================================================================
    float getVelocityDepth();
    float getVelocityVariance();
    String getVelocityDirection();
    void cycleVelocityDirection();
    void handleVelocityDepthSlider (float velocityDepth);
    void handleVelocityVarianceSlider (float velocityVariance);

    //==============================================================================
    XmlElement* exportControlsStateXml();
    void importControlsStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    int mTransposeBase = 21;
    int mActiveTransposeNote = -1;
    Transpose mTranspose = Transpose::Off;

    float mTimingDepth = 0.f;
    float mTimingVariance = 0.f;
    String mTimingDirection = "LTR";

    float mVelocityDepth = 0.f;
    float mVelocityVariance = 0.f;
    String mVelocityDirection = "HTS";

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
