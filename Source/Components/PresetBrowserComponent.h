#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "PresetComponent.h"
#include "PresetTaggerComponent.h"
#include "DataMessageListener.h"

//==============================================================================
class PresetBrowserComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    PresetBrowserComponent (MainProcess&);
    ~PresetBrowserComponent();

    //==============================================================================
    void setDimensions (int width, int height);

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    PresetState& mPresetState;
    BrowserState& mBrowserState;

    int mPresetHeight = 0;
    int mPresetWidth = 0;
    int mSpaceHeight = 0;
    int mSpaceWidth = 0;

    void hardRefresh();
    void refreshBrowser();

    OwnedArray<PresetComponent> mPresetsToDelete;
    OwnedArray<PresetTaggerComponent> mPresetTaggersToDelete;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetBrowserComponent)
};
