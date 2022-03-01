#pragma once

#include "JuceHeader.h"
#include "MainProcess.h"
#include "TagComponent.h"
#include "DataMessageListener.h"

//==============================================================================
class TagBarComponent : public Component, public DataMessageListener
{
public:
    //==============================================================================
    TagBarComponent (MainProcess&);
    ~TagBarComponent();

    //==============================================================================
    void setDimensions (int width, int height);

    //==============================================================================
    void handleNewMessage (const DataMessage* message) override;

private:
    //==============================================================================
    MainProcess& mMainProcess;
    GlobalState& mGlobalState;
    BrowserState& mBrowserState;

    int mTagHeight = 0;
    int mTagWidth = 0;
    int mSpaceHeight = 0;
    int mSpaceWidth = 0;

    void refreshBrowser();

    OwnedArray<TagComponent> mTagsToDelete;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TagBarComponent)
};
