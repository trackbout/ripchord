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
    mTagWidth = int (inWidth * (TAG_WIDTH / TAG_BROWSER_WIDTH));
    mSpaceWidth = (inWidth - (TAGS_PER_ROW * mTagWidth)) / (TAGS_PER_ROW + 1);

    mTagHeight = int (inHeight * (ITEM_HEIGHT / PRESET_VIEWPORT_HEIGHT));
    mSpaceHeight = mTagHeight * (HALF_SPACE / ITEM_HEIGHT);

    refreshBrowser();
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
    mBrowserState.refreshData();
    refreshBrowser();
}

void TagBrowserComponent::refreshBrowser()
{
    if (mGlobalState.isKeyboardView()) { return; }

    removeAllChildren();
    StringArray tagNames = mBrowserState.getTagNames();

    for (int index = 0; index < tagNames.size(); index++)
    {
        // do stuff
    }
}
