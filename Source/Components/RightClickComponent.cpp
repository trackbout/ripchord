#include "RightClickComponent.h"

//==============================================================================
RightClickComponent::RightClickComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mCutButton, "RightClickCut.svg");
    mImages.setDrawableButtonImages (mCopyButton, "RightClickCopy.svg");
    mImages.setDrawableButtonImages (mPasteButton, "RightClickPaste.svg");
    mImages.setDrawableButtonImages (mRightClickBg, "RightClickBgLIGHT.svg");

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

    mRightClickBg.setBounds (Styles::getRelativeBounds (mainArea, mouseDownX, mouseDownY, RIGHT_CLICK_MENU_WIDTH, RIGHT_CLICK_MENU_HEIGHT));
    mCutButton.setBounds (Styles::getRelativeBounds (mainArea, mouseDownX + 10, mouseDownY + 9, RIGHT_CLICK_ITEM_WIDTH, RIGHT_CLICK_ITEM_HEIGHT));
    mCopyButton.setBounds (Styles::getRelativeBounds (mainArea, mouseDownX + 10, mouseDownY + 39, RIGHT_CLICK_ITEM_WIDTH, RIGHT_CLICK_ITEM_HEIGHT));
    mPasteButton.setBounds (Styles::getRelativeBounds (mainArea, mouseDownX + 10, mouseDownY + 69, RIGHT_CLICK_ITEM_WIDTH, RIGHT_CLICK_ITEM_HEIGHT));

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mRightClickBg, isDark ? "RightClickBgDARK.svg" : "RightClickBgLIGHT.svg");
}

//==============================================================================
void RightClickComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleRight): { handleToggleRightClick (inMessage); } break;
        case (MessageCode::kToggleTheme): { handleToggleTheme (inMessage); } break;
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

void RightClickComponent::handleToggleTheme (const DataMessage* inMessage)
{
    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mRightClickBg, isDark ? "RightClickBgDARK.svg" : "RightClickBgLIGHT.svg");
}
