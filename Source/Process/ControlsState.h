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
    enum Transpose { Off, On };

    //==============================================================================
    bool isTransposeOff();
    bool isTransposeOn();

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
    XmlElement* exportControlsStateXml();
    void importControlsStateXml (XmlElement* presetStateXml);

private:
    //==============================================================================
    Transpose mTranspose = Transpose::Off;

    int mTransposeBase = 21;
    int mActiveTransposeNote = -1;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsState)
};
