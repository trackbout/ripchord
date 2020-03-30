#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class EditControlsComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    EditControlsComponent (MainProcess&);
    ~EditControlsComponent();

    //==============================================================================
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;
    MidiState& mMidiState;

    Images mImages;
    DrawableButton mAllWhiteButton { "", DrawableButton::ImageStretched };
    DrawableButton mAllBlackButton { "", DrawableButton::ImageStretched };
    DrawableButton mEditRightButton { "", DrawableButton::ImageStretched };
    DrawableButton mEditLeftButton { "", DrawableButton::ImageStretched };
    DrawableButton mSaveButton { "", DrawableButton::ImageStretched };
    DrawableButton mSuccess { "", DrawableButton::ImageStretched };

    void handleToggleMode (const DataMessage* message);
    void handlePresetFileNew (const DataMessage* message);
    void handlePresetFileSaved (const DataMessage* message);
    void handlePresetFileLoaded (const DataMessage* message);
    void handlePresetModified (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditControlsComponent)
};
