#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class ControlsComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    ControlsComponent (MainProcess&);
    ~ControlsComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    ControlsState& mControlsState;
    MidiState& mMidiState;

    Images mImages;

    DrawableButton mVelocityDepthImage { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityDirectionButton { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityVarianceImage { "", DrawableButton::ImageStretched };

    DrawableButton mShiftLeftButton { "", DrawableButton::ImageStretched };
    DrawableButton mTransposeButton { "", DrawableButton::ImageStretched };
    DrawableButton mShiftRightButton { "", DrawableButton::ImageStretched };

    DrawableButton mTimingVarianceImage { "", DrawableButton::ImageStretched };
    DrawableButton mTimingDirectionButton { "", DrawableButton::ImageStretched };
    DrawableButton mTimingDepthImage { "", DrawableButton::ImageStretched };

    Slider mVelocityDepthSlider;
    Slider mVelocityVarianceSlider;
    Slider mTimingDepthSlider;
    Slider mTimingVarianceSlider;

    void handleToggleMode (const DataMessage* message);
    void handleToggleTranspose (const DataMessage* message);
    void handleToggleTimingDirection (const DataMessage* message);
    void handleToggleVelocityDirection (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
