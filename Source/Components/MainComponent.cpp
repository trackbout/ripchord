#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mKeyboardViewComponent (inMainProcess),
    mPresetViewComponent (inMainProcess),
    mRightClickComponent (inMainProcess),
    mMenuComponent (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mGlobalState.setThemeFromConfig();

    setOpaque (true);
    mTitleLabel.setFont (Font().boldened());
    mTitleLabel.setColour (Label::textColourId, COLOR_PURPLE);

    addAndMakeVisible (mTitleLabel);
    addAndMakeVisible (mKeyboardViewComponent);
    addChildComponent (mPresetViewComponent);

    addChildComponent (mMenuComponent);
    addChildComponent (mRightClickComponent);

    mShouldReconstruct = true;
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (mGlobalState.isDarkTheme() ? COLOR_THEME_DARK : COLOR_THEME_LIGHT);
    inGraphics.fillRect (getLocalBounds());

    if (mShouldReconstruct)
    {
        reconstruct();
        mShouldReconstruct = false;
    }
}

void MainComponent::resized()
{
    auto mainArea = getLocalBounds();
    mKeyboardViewComponent.setBounds (mainArea);
    mPresetViewComponent.setBounds (mainArea);
    mRightClickComponent.setBounds (mainArea);
    mMenuComponent.setBounds (mainArea);

    auto titleArea = Styles::getRelativeBounds (mainArea, SPACE - 4, HEADER_Y, BUTTON_WIDTH + 10, ITEM_HEIGHT - 2);
    mTitleLabel.setFont (Font ((float) titleArea.getHeight()).boldened());
    mTitleLabel.setBounds (titleArea);
}

//==============================================================================
void MainComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { handleToggleView (inMessage); } break;
        case (MessageCode::kToggleMenu): { handleToggleMenu (inMessage); } break;
        case (MessageCode::kToggleTheme): { handleToggleTheme (inMessage); } break;
        case (MessageCode::kToggleRight): { handleToggleRightClick (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        default: { } break;
    };
}

void MainComponent::handleToggleView (const DataMessage* inMessage)
{
    mKeyboardViewComponent.setVisible (!mGlobalState.isPresetView());
    mPresetViewComponent.setVisible (mGlobalState.isPresetView());
}

void MainComponent::handleToggleMenu (const DataMessage* inMessage)
{
    mMenuComponent.setVisible (mGlobalState.isMenuVisible());
}

void MainComponent::handleToggleTheme (const DataMessage* inMessage)
{
    repaint();
}

void MainComponent::handleToggleRightClick (const DataMessage* inMessage)
{
    mRightClickComponent.setVisible (mGlobalState.isRightClickOn());
}

void MainComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    if (mGlobalState.isPlayMode()) { mGlobalState.toggleMode(); }
    if (mGlobalState.isPresetView()) { mGlobalState.toggleView(); }
}

void MainComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    if (mGlobalState.isEditMode()) { mGlobalState.toggleMode(); }
    if (mGlobalState.isPresetView()) { mGlobalState.toggleView(); }
}

void MainComponent::reconstruct()
{
    if (mGlobalState.isPlayMode()) { mGlobalState.toggleMode(); }
    if (mGlobalState.isMenuVisible()) { mGlobalState.toggleMenu(); }
    if (mGlobalState.isPresetView()) { mGlobalState.toggleView(); }
    if (mGlobalState.isEditMode()) { mGlobalState.toggleMode(); }
}
