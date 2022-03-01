#include "JuceHeader.h"
#include "TagBarComponent.h"

//==============================================================================
TagBarComponent::TagBarComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

TagBarComponent::~TagBarComponent()
{
}

//==============================================================================
void TagBarComponent::setDimensions (int inWidth, int inHeight)
{

}

//==============================================================================
void TagBarComponent::handleNewMessage (const DataMessage* inMessage)
{

}

//==============================================================================
void TagBarComponent::refreshBrowser()
{

}
