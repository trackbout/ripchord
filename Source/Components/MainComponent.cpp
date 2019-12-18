#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mKeyboardViewComponent (inMainProcess),
    mPresetViewComponent (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, kListenerType_Sync);

    setOpaque (true);
    mTitleLabel.setFont (Font().boldened());
    mTitleLabel.setColour (Label::textColourId, COLOR_PURPLE);

    mImages.setDrawableButtonImages (mMenuButton, "Gear.svg");
    mMenuButton.setTriggeredOnMouseDown (true);
    mMenuButton.onClick = [this]() { mGlobalState.toggleMenu(); };

    addAndMakeVisible (mTitleLabel);
    addAndMakeVisible (mKeyboardViewComponent);
    addChildComponent (mPresetViewComponent);

    addAndMakeVisible (mMenuButton);
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

    auto titleArea = Interface::getRelativeBounds (mainArea, SPACE - 4, HEADER_Y, BUTTON_WIDTH + 10, ITEM_HEIGHT - 2);
    mTitleLabel.setFont (Font ((float) titleArea.getHeight()).boldened());
    mTitleLabel.setBounds (titleArea);

    auto menuButtonArea = Interface::getRelativeBounds (mainArea, ACTIONS_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT);
    mMenuButton.setBounds (menuButtonArea);
}

//==============================================================================
void MainComponent::messageReceived (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (DataMessageCode::kViewUpdated):
        {
            handleViewUpdated();
        } break;

        default: {} break;
    };
}

void MainComponent::handleViewUpdated()
{
    mKeyboardViewComponent.setVisible (!mGlobalState.isPresetView());
    mPresetViewComponent.setVisible (mGlobalState.isPresetView());
}
