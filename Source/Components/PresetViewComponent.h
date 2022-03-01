#pragma once

#include "JuceHeader.h"
#include "Images.h"
#include "Styles.h"
#include "MainProcess.h"
#include "TagBarComponent.h"
#include "TagManagerComponent.h"
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

    Viewport mTagBarViewport;
    Viewport mPresetViewport;

    TagBarComponent mTagBar;
    TagManagerComponent mTagManager;
    PresetBrowserComponent mPresetBrowser;
    TextEditor mPresetFilterInput;

    Images mImages;
    DrawableButton mTagBarBg { "", DrawableButton::ImageStretched };
    DrawableButton mSearchBarBg { "", DrawableButton::ImageStretched };
    DrawableButton mPresetBrowserBg { "", DrawableButton::ImageStretched };
    DrawableButton mMenuButton { "", DrawableButton::ImageStretched };
    DrawableButton mPowerButton { "", DrawableButton::ImageStretched };
    DrawableButton mTagManagerButton { "", DrawableButton::ImageStretched };
    DrawableButton mTagSelectorButton { "", DrawableButton::ImageStretched };
    DrawableButton mFavoritesButton { "", DrawableButton::ImageStretched };
    DrawableButton mKeyboardsButton { "", DrawableButton::ImageStretched };

    void handleToggleView (const DataMessage* message);
    void handleToggleFavorites (const DataMessage* message);
    void handleToggleTagManager (const DataMessage* message);
    void handleToggleTagSelector (const DataMessage* message);
    void handlePresetFilterTextChanged (const DataMessage* message);

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetViewComponent)
};
