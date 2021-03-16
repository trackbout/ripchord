#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"
#include "RecordedMidiComponent.h"

//==============================================================================
class PlayControlsComponent : public Component, public DataMessageListener, public Slider::Listener
{
public:
    //==============================================================================
    PlayControlsComponent (MainProcess&);
    ~PlayControlsComponent();

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

    RecordedMidiComponent mRecordedMidi;

    DrawableButton mVelocityDirectionButton { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityDepthImage { "", DrawableButton::ImageStretched };
    DrawableButton mVelocityVarianceImage { "", DrawableButton::ImageStretched };

    DrawableButton mShiftLeftButton { "", DrawableButton::ImageStretched };
    DrawableButton mTransposeButton { "", DrawableButton::ImageStretched };
    DrawableButton mShiftRightButton { "", DrawableButton::ImageStretched };

    DrawableButton mDelayVarianceImage { "", DrawableButton::ImageStretched };
    DrawableButton mDelayDepthImage { "", DrawableButton::ImageStretched };
    DrawableButton mDelayDirectionButton { "", DrawableButton::ImageStretched };

    DrawableButton mRecordButton { "", DrawableButton::ImageStretched };

    Slider mVelocityDepthSlider;
    Slider mVelocityVarianceSlider;
    Slider mDelayDepthSlider;
    Slider mDelayVarianceSlider;

    void handleToggleMode (const DataMessage* message);
    void handleIsRecording (const DataMessage* message);
    void handleToggleRecord (const DataMessage* message);
    void handleToggleTranspose (const DataMessage* message);

    void handleDelayDepth (const DataMessage* message);
    void handleDelayDirection (const DataMessage* message);
    void handleDelayVariance (const DataMessage* message);

    void handleVelocityDepth (const DataMessage* message);
    void handleVelocityDirection (const DataMessage* message);
    void handleVelocityVariance (const DataMessage* message);

    void updateRecordButtons();
    void updateTransposeButton();
    void updateDelayControlImages();
    void updateDelayVarianceImage();
    void updateVelocityControlImages();
    void updateVelocityVarianceImage();

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayControlsComponent)
};
