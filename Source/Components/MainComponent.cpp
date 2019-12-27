#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mKeyboardViewComponent (inMainProcess),
    mPresetViewComponent (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setOpaque (true);
    mTitleLabel.setFont (Font().boldened());
    mTitleLabel.setColour (Label::textColourId, COLOR_PURPLE);

    mImages.setDrawableButtonImages (mMenuButton, "Gear.svg");
    mMenuButton.setTriggeredOnMouseDown (true);
    mMenuButton.onClick = [this]() { mGlobalState.toggleMenu(); };
    mMenuComponent.handleBackgroundClick = [this]() { mGlobalState.toggleMenu(); };

    addAndMakeVisible (mTitleLabel);
    addAndMakeVisible (mKeyboardViewComponent);
    addChildComponent (mPresetViewComponent);

    addAndMakeVisible (mMenuButton);
    addChildComponent (mMenuComponent);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY_LIGHTEST);
    inGraphics.fillRect (getLocalBounds());
}

void MainComponent::resized()
{
    auto mainArea = getLocalBounds();
    mKeyboardViewComponent.setBounds (mainArea);
    mPresetViewComponent.setBounds (mainArea);
    mMenuComponent.setBounds (mainArea);

    auto titleArea = Interface::getRelativeBounds (mainArea, SPACE - 4, HEADER_Y, BUTTON_WIDTH + 10, ITEM_HEIGHT - 2);
    mTitleLabel.setFont (Font ((float) titleArea.getHeight()).boldened());
    mTitleLabel.setBounds (titleArea);

    auto menuButtonArea = Interface::getRelativeBounds (mainArea, ACTIONS_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT);
    mMenuButton.setBounds (menuButtonArea);
}

//==============================================================================
void MainComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kViewUpdated): { handleViewUpdated(); } break;
        case (MessageCode::kMenuUpdated): { handleMenuUpdated(); } break;
        default: { } break;
    };
}

void MainComponent::handleViewUpdated()
{
    mKeyboardViewComponent.setVisible (!mGlobalState.isPresetView());
    mPresetViewComponent.setVisible (mGlobalState.isPresetView());
}

void MainComponent::handleMenuUpdated()
{
    mMenuComponent.setVisible (mGlobalState.isMenuVisible());
}
