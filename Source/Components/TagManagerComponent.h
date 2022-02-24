#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "DataMessageListener.h"

//==============================================================================
class TagManagerComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    TagManagerComponent (MainProcess&);
    ~TagManagerComponent();

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
    BrowserState& mBrowserState;

    TextEditor mNewTagInput;

    Images mImages;
    DrawableButton mNewTagBg { "", DrawableButton::ImageStretched };
    DrawableButton mBackground { "", DrawableButton::ImageStretched };

    //==============================================================================
    void handleToggleTagManager (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TagManagerComponent)
};
