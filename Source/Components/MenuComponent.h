#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class MenuComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    MenuComponent (MainProcess&);
    ~MenuComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& event) override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    Images mImages;
    Label mTitleLabel { "", "ripchord 2.5.0" };
    Label mColorLabel { "", "color mode" };
    Label mLegatoLabel { "", "legato mode" };

    DrawableButton mColorMode { "", DrawableButton::ImageStretched };
    DrawableButton mLegatoMode { "", DrawableButton::ImageStretched };

    DrawableButton mBackground { "", DrawableButton::ImageStretched };
    DrawableButton mNewPresetButton { "", DrawableButton::ImageStretched };
    DrawableButton mDuplicateButton { "", DrawableButton::ImageStretched };
    DrawableButton mImportMidiButton { "", DrawableButton::ImageStretched };
    DrawableButton mExportMidiButton { "", DrawableButton::ImageStretched };
    DrawableButton mImportPresetButton { "", DrawableButton::ImageStretched };
    DrawableButton mExportPresetButton { "", DrawableButton::ImageStretched };
    DrawableButton mCommunityButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    void handleToggleMenu (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuComponent)
};
