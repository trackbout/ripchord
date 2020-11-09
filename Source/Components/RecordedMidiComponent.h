#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "Images.h"
#include "Styles.h"

//==============================================================================
class RecordedMidiComponent : public Component, public DragAndDropContainer
{
public:
    //==============================================================================
    RecordedMidiComponent (MainProcess&);
    ~RecordedMidiComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& event) override;

    //==============================================================================
    void setButtonImage (const String imagePath);

private:
    //==============================================================================
    MainProcess& mMainProcess;
    MidiState& mMidiState;

    Images mImages;

    DrawableButton mRecordedButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RecordedMidiComponent)
};
