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
    int getTimingDepth();
    int getTimingVariance();
    String getTimingDirection();
    void cycleTimingDirection();
    void handleTimingDepthSlider (int timingDepth);
    void handleTimingVarianceSlider (int timingVariance);

    //==============================================================================
    int getVelocityDepth();
    int getVelocityVariance();
    String getVelocityDirection();
    void cycleVelocityDirection();
    void handleVelocityDepthSlider (int velocityDepth);
    void handleVelocityVarianceSlider (int velocityVariance);

    //==============================================================================
    XmlElement* exportControlsStateXml();
    void importControlsStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    int mTransposeBase = 21;
    int mActiveTransposeNote = -1;
    Transpose mTranspose = Transpose::Off;

    int mTimingDepth = 0;
    int mTimingVariance = 0;
    String mTimingDirection = "LTR";

    int mVelocityDepth = 0;
    int mVelocityVariance = 0;
    String mVelocityDirection = "HTS";

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
