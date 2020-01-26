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

    DrawableButton mVelocityDepth { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityAlternate { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityVariance { "", DrawableButton::ImageStretched };

    DrawableButton mShiftLeftButton { "", DrawableButton::ImageStretched };
    DrawableButton mTransposeButton { "", DrawableButton::ImageStretched };
    DrawableButton mShiftRightButton { "", DrawableButton::ImageStretched };

    DrawableButton mTimingVariance { "", DrawableButton::ImageStretched };
    DrawableButton mTimingAlternate { "", DrawableButton::ImageStretched };
    DrawableButton mTimingDepth { "", DrawableButton::ImageStretched };

    void handleToggleMode (const DataMessage* message);
    void handleToggleTranspose (const DataMessage* message);

    bool isTransposeShiftDisabled();
    bool isTransposeToggleDisabled();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlsComponent)
};
