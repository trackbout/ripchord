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
        mGlobalState.toggleRightClick();
        mPresetState.handleMouseDownOnCut (mGlobalState.getMouseDownKey());
    };

    mCopyButton.onClick = [this]()
    {
        mGlobalState.toggleRightClick();
        mPresetState.handleMouseDownOnCopy (mGlobalState.getMouseDownKey());
    };

    mPasteButton.onClick = [this]()
    {
        mGlobalState.toggleRightClick();
        mPresetState.handleMouseDownOnPaste (mGlobalState.getMouseDownKey());
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
    paintWithCoordinates();
}

//==============================================================================
void RightClickComponent::mouseDown (const MouseEvent& inEvent)
{
    mGlobalState.toggleRightClick();
}

//==============================================================================
void RightClickComponent::paintWithCoordinates()
{
    auto mainArea = getLocalBounds();
    int mouseDownKey = mGlobalState.getMouseDownKey();
    int xOffset = mouseDownKey < 104 ? KEYBOARD_X : KEYBOARD_X - RIGHT_CLICK_MENU_WIDTH;
    int mouseDownX = mGlobalState.getMouseDownX() + xOffset;
    int mouseDownY = mGlobalState.getMouseDownY() + INPUT_KEYBOARD_Y - RIGHT_CLICK_MENU_HEIGHT;

    auto menuArea = Styles::getRelativeBounds (mainArea, mouseDownX, mouseDownY,
                                               RIGHT_CLICK_MENU_WIDTH, RIGHT_CLICK_MENU_HEIGHT);

    int menuHeight = menuArea.getHeight();
    int buttonHeight = menuHeight / RIGHT_CLICK_ITEM_COUNT;

    mRightClickBg.setBounds (menuArea);
    mCutButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mCopyButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mPasteButton.setBounds (menuArea.removeFromTop (buttonHeight));
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
    if (mGlobalState.isRightClickOn())
    {
        paintWithCoordinates();
    }
}
