#include "TagManagerComponent.h"

//==============================================================================
TagManagerComponent::TagManagerComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mBrowserState (mMainProcess.getBrowserState())
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

TagManagerComponent::~TagManagerComponent()
{
}

//==============================================================================
void TagManagerComponent::paint (Graphics& inGraphics)
{

}

void TagManagerComponent::resized()
{

}

//==============================================================================
void TagManagerComponent::mouseDown (const MouseEvent& inEvent)
{

}

//==============================================================================
void TagManagerComponent::handleNewMessage (const DataMessage* inMessage)
{

}
