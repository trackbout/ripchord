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
    mSpaceHeight = mTagHeight * ((HALF_SPACE + 4) / ITEM_HEIGHT);

    refreshBrowser();
}

//==============================================================================
void TagBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { refreshBrowser(); } break;
        case (MessageCode::kTagCreated): { hardRefresh(); } break;
        case (MessageCode::kTagDeleted): { hardRefresh(); } break;
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
        String tagName = tagNames[index];
        int x = (index % TAGS_PER_ROW) * (mTagWidth + mSpaceWidth) + mSpaceWidth;
        int y = (index / TAGS_PER_ROW) * (mTagHeight + mSpaceHeight) + mSpaceHeight;

        auto* tagComponent = new TagComponent (tagName);
        tagComponent->setBounds (x, y, mTagWidth, mTagHeight);

        tagComponent->onDelete = [this](const String name)
        {
            mBrowserState.handleClickDeleteTag (name);
        };

        addAndMakeVisible (tagComponent);

        // Delete pointers to prevent leaks
        mTagsToDelete.add (tagComponent);
    }

    int rowCount = (int) std::ceil (tagNames.size() / (float) (TAGS_PER_ROW));
    int viewportHeight = ((mTagHeight + mSpaceHeight) * rowCount) + mSpaceHeight;
    setSize (getWidth(), viewportHeight);
}
