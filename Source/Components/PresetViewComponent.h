#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "PresetBrowserComponent.h"
#include "DataMessageListener.h"
#include "DataMessage.h"

//==============================================================================
class PresetViewComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    PresetViewComponent (MainProcess&);
    ~PresetViewComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    BrowserState& mBrowserState;

    Images mImages;
    Viewport mPresetViewport;
    TextEditor mPresetFilterInput;
    PresetBrowserComponent mPresetBrowser;

    DrawableButton mFavoritesButton { "", DrawableButton::ImageStretched };
    DrawableButton mKeyboardsButton { "", DrawableButton::ImageStretched };

    void handleToggleFavorites (const DataMessage* message);
    void handlePresetFilterTextChanged (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewComponent)
};
