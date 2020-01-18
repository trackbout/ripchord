#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "PresetComponent.h"
#include "DataMessageListener.h"
#include "DataMessage.h"

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
    BrowserState& mBrowserState;

    int mPresetHeight = 0;
    int mPresetWidth = 0;
    int mSpaceHeight = 0;
    int mSpaceWidth = 0;

    OwnedArray<PresetComponent> mPresetsToDelete;

    void refreshBrowser (juce::Array<juce::Array<String>> presetNames);

    void handleViewUpdated (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetBrowserComponent)
};
