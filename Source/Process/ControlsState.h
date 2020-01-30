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
    enum class Transpose { On, Off };
    enum class TimingDirection { On, Off };
    enum class VelocityDirection { On, Off };

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
    bool isTimingDirectionOn();
    bool isTimingDirectionOff();
    void toggleTimingDirection();

    //==============================================================================
    bool isVelocityDirectionOn();
    bool isVelocityDirectionOff();
    void toggleVelocityDirection();

    //==============================================================================
    XmlElement* exportControlsStateXml();
    void importControlsStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    Transpose mTranspose = Transpose::Off;
    TimingDirection mTimingDirection = TimingDirection::Off;
    VelocityDirection mVelocityDirection = VelocityDirection::Off;

    int mTransposeBase = 21;
    int mActiveTransposeNote = -1;

    float mTimingDepth = 0.f;
    float mTimingVariance = 0.f;

    float mVelocityDepth = 0.f;
    float mVelocityVariance = 0.f;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
