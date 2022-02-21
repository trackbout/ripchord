#include "TagManagerComponent.h"

//==============================================================================
TagManagerComponent::TagManagerComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");

    addAndMakeVisible (mBackground);
}

TagManagerComponent::~TagManagerComponent()
{
}

//==============================================================================
void TagManagerComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_OVERLAY);
    inGraphics.fillRect (getLocalBounds());
}

void TagManagerComponent::resized()
{
    auto mainArea = getLocalBounds();
    mBackground.setBounds (Styles::getRelativeBounds (mainArea, MODAL_X, MODAL_Y, MODAL_WIDTH, MODAL_HEIGHT));
}

//==============================================================================
void TagManagerComponent::mouseDown (const MouseEvent& inEvent)
{
    mBrowserState.toggleTagManager();
}

//==============================================================================
void TagManagerComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleTagManager): { handleToggleTagManager (inMessage); } break;
        default: { } break;
    };
}

void TagManagerComponent::handleToggleTagManager (const DataMessage* inMessage)
{
    if (mBrowserState.isTagManagerHidden()) { return; }

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");
}
