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
    mTagWidth = float (inWidth * (BROWSER_TAG_WIDTH / TAG_BROWSER_WIDTH));
    mSpaceWidth = (inWidth - (BROWSER_TAGS_PER_ROW * mTagWidth)) / (BROWSER_TAGS_PER_ROW + 1);

    mTagHeight = float (inHeight * (ITEM_HEIGHT / PRESET_VIEWPORT_HEIGHT));
    mSpaceHeight = mTagHeight * ((HALF_SPACE + 4) / ITEM_HEIGHT);

    refreshBrowser();
}

//==============================================================================
void TagBrowserComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { refreshBrowser(); } break;
        case (MessageCode::kTagCreated): { refreshBrowser(); } break;
        case (MessageCode::kTagDeleted): { refreshBrowser(); } break;
        case (MessageCode::kTagShifted): { refreshBrowser(); } break;
        default: { } break;
    };
}

//==============================================================================
void TagBrowserComponent::refreshBrowser()
{
    if (mGlobalState.isKeyboardView()) { return; }

    removeAllChildren();
    StringArray allTagNames = mBrowserState.getAllTagNames();

    for (int index = 0; index < allTagNames.size(); index++)
    {
        String tagName = allTagNames[index];
        float x = (index % BROWSER_TAGS_PER_ROW) * (mTagWidth + mSpaceWidth) + mSpaceWidth;
        float y = (index / BROWSER_TAGS_PER_ROW) * (mTagHeight + mSpaceHeight) + mSpaceHeight;

        auto* tagComponent = new TagComponent (tagName, "browser", false, false);
        tagComponent->setBounds (x, y, mTagWidth, mTagHeight);

        tagComponent->onUpShift = [this](const String name)
        {
            mBrowserState.handleClickShiftTag (name, "UP");
        };

        tagComponent->onDownShift = [this](const String name)
        {
            mBrowserState.handleClickShiftTag (name, "DOWN");
        };

        tagComponent->onDelete = [this](const String name)
        {
            mBrowserState.handleClickDeleteTag (name);
        };

        addAndMakeVisible (tagComponent);

        // Delete pointers to prevent leaks
        mTagsToDelete.add (tagComponent);
    }

    int rowCount = (int) std::ceil (allTagNames.size() / (float) (BROWSER_TAGS_PER_ROW));
    float viewportHeight = ((mTagHeight + mSpaceHeight) * rowCount) + mSpaceHeight;
    setSize (getWidth(), viewportHeight);
}
