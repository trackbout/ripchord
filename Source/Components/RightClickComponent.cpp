#include "RightClickComponent.h"

//==============================================================================
RightClickComponent::RightClickComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mCutButton, "Cut.svg");
    mImages.setDrawableButtonImages (mCopyButton, "Copy.svg");
    mImages.setDrawableButtonImages (mPasteButton, "Paste.svg");
    mImages.setDrawableButtonImages (mRightClickBg, "RightClick.svg");

    mCutButton.setTriggeredOnMouseDown (true);
    mCopyButton.setTriggeredOnMouseDown (true);
    mPasteButton.setTriggeredOnMouseDown (true);

    mCutButton.onClick = [this]()
    {
        DBG ("CUT");
    };

    mCopyButton.onClick = [this]()
    {
        DBG ("COPY");
    };

    mPasteButton.onClick = [this]()
    {
        DBG ("PASTE");
    };

    addAndMakeVisible (mRightClickBg);
    addAndMakeVisible (mCutButton);
    addAndMakeVisible (mCopyButton);
    addAndMakeVisible (mPasteButton);
}

RightClickComponent::~RightClickComponent()
{
}

//==============================================================================
void RightClickComponent::resized()
{
    auto mainArea = getLocalBounds();
    auto menuArea = Styles::getRelativeBounds (mainArea, RIGHT_CLICK_MENU_X, RIGHT_CLICK_MENU_Y,
                                               RIGHT_CLICK_MENU_WIDTH, RIGHT_CLICK_MENU_HEIGHT);

    int menuHeight = menuArea.getHeight();
    int buttonHeight = menuHeight / RIGHT_CLICK_ITEM_COUNT;

    mRightClickBg.setBounds (menuArea);
    mCutButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mCopyButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mPasteButton.setBounds (menuArea.removeFromTop (buttonHeight));
}

//==============================================================================
void RightClickComponent::mouseDown (const MouseEvent& inEvent)
{
    if (handleBackgroundClick) { handleBackgroundClick(); }
}

//==============================================================================
void RightClickComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleRight): { handleToggleRightClick (inMessage); } break;
        default: { } break;
    };
}

void RightClickComponent::handleToggleRightClick (const DataMessage* inMessage)
{

}
