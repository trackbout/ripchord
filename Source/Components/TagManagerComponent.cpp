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

}

//==============================================================================
void TagManagerComponent::handleNewMessage (const DataMessage* inMessage)
{

}
