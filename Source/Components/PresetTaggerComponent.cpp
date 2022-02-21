#include "PresetTaggerComponent.h"

//==============================================================================
PresetTaggerComponent::PresetTaggerComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mBrowserState (mMainProcess.getBrowserState())
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

PresetTaggerComponent::~PresetTaggerComponent()
{
}

//==============================================================================
void PresetTaggerComponent::paint (Graphics& inGraphics)
{

}

void PresetTaggerComponent::resized()
{

}

//==============================================================================
void PresetTaggerComponent::mouseDown (const MouseEvent& inEvent)
{

}

//==============================================================================
void PresetTaggerComponent::handleNewMessage (const DataMessage* inMessage)
{

}
