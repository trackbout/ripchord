#include "PresetTaggerComponent.h"

//==============================================================================
PresetTaggerComponent::PresetTaggerComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");

    addAndMakeVisible (mBackground);
}

PresetTaggerComponent::~PresetTaggerComponent()
{
}

//==============================================================================
void PresetTaggerComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_OVERLAY);
    inGraphics.fillRect (getLocalBounds());
}

void PresetTaggerComponent::resized()
{
    auto mainArea = getLocalBounds();
    mBackground.setBounds (Styles::getRelativeBounds (mainArea, MODAL_X, MODAL_Y, MODAL_WIDTH, MODAL_HEIGHT));
}

//==============================================================================
void PresetTaggerComponent::mouseDown (const MouseEvent& inEvent)
{

}

//==============================================================================
void PresetTaggerComponent::handleNewMessage (const DataMessage* inMessage)
{

}
