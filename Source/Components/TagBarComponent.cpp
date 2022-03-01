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
    const float widthRatio = inWidth / TAG_BAR_WIDTH;
    const float heightRatio = inHeight / TAG_BAR_HEIGHT;

    mTagWidth = widthRatio * BAR_TAG_WIDTH;
    mSpaceWidth = widthRatio * (HALF_SPACE / 2);

    mTagHeight = heightRatio * BAR_TAG_HEIGHT;
    mSpaceHeight = heightRatio * ((ITEM_HEIGHT - BAR_TAG_HEIGHT) / 2);

    refreshBrowser();
}

//==============================================================================
void TagBarComponent::handleNewMessage (const DataMessage* inMessage)
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
void TagBarComponent::hardRefresh()
{
    mBrowserState.refreshData();
    refreshBrowser();
}

void TagBarComponent::refreshBrowser()
{
    if (mGlobalState.isKeyboardView()) { return; }

    removeAllChildren();
    StringArray tagNames = mBrowserState.getTagNames();

    for (int index = 0; index < tagNames.size(); index++)
    {
        String tagName = tagNames[index];
        float x = (index * (mTagWidth + mSpaceWidth)) + mSpaceWidth;
        float y = mSpaceHeight - 0.5f;

        auto* tagComponent = new TagComponent (tagName);
        tagComponent->setBounds (x, y, mTagWidth, mTagHeight);

        tagComponent->onDelete = [this](const String name) { };

        addAndMakeVisible (tagComponent);

        // Delete pointers to prevent leaks
        mTagsToDelete.add (tagComponent);
    }

    float viewportWidth = ((mTagWidth + mSpaceWidth) * tagNames.size()) + mSpaceWidth;
    setSize (viewportWidth, getHeight());
}
