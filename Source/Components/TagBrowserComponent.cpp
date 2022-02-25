#include "JuceHeader.h"
#include "TagBrowserComponent.h"

//==============================================================================
TagBrowserComponent::TagBrowserComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

TagBrowserComponent::~TagBrowserComponent()
{
}

//==============================================================================
void TagBrowserComponent::setDimensions (int inWidth, int inHeight)
{

}

//==============================================================================
void TagBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { hardRefresh(); } break;
        default: { } break;
    };
}

//==============================================================================
void TagBrowserComponent::hardRefresh()
{

}

void TagBrowserComponent::refreshBrowser()
{

}
