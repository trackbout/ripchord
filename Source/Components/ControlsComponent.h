#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class ControlsComponent : public Component, public DataMessageListener, public Slider::Listener
{
public:
    //==============================================================================
    ControlsComponent (MainProcess&);
    ~ControlsComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void sliderValueChanged (Slider* slider) override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    ControlsState& mControlsState;
    MidiState& mMidiState;

    Images mImages;

    DrawableButton mVelocityDirectionButton { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityDepthImage { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityVarianceImage { "", DrawableButton::ImageStretched };

    DrawableButton mShiftLeftButton { "", DrawableButton::ImageStretched };
    DrawableButton mTransposeButton { "", DrawableButton::ImageStretched };
    DrawableButton mShiftRightButton { "", DrawableButton::ImageStretched };

    DrawableButton mTimingVarianceImage { "", DrawableButton::ImageStretched };
    DrawableButton mTimingDepthImage { "", DrawableButton::ImageStretched };
    DrawableButton mTimingDirectionButton { "", DrawableButton::ImageStretched };

    Slider mVelocityDepthSlider;
    Slider mVelocityVarianceSlider;
    Slider mTimingDepthSlider;
    Slider mTimingVarianceSlider;

    void handleToggleMode (const DataMessage* message);
    void handleToggleTranspose (const DataMessage* message);

    void handleTimingDepth (const DataMessage* message);
    void handleTimingVariance (const DataMessage* message);
    void handleTimingDirection (const DataMessage* message);

    void handleVelocityDepth (const DataMessage* message);
    void handleVelocityVariance (const DataMessage* message);
    void handleVelocityDirection (const DataMessage* message);

    void updateTransposeButton();
    void updateTimingDirectionButton();
    void updateVelocityDirectionButton();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
