#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class RightClickComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    RightClickComponent (MainProcess&);
    ~RightClickComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void mouseDown (const MouseEvent& event) override;
    std::function<void()> handleBackgroundClick;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;

    Images mImages;
    DrawableButton mCutButton { "", DrawableButton::ImageStretched };
    DrawableButton mCopyButton { "", DrawableButton::ImageStretched };
    DrawableButton mPasteButton { "", DrawableButton::ImageStretched };

    //==============================================================================
    void handleToggleMenu (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RightClickComponent)
};
