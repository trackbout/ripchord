#include "TagManagerComponent.h"

//==============================================================================
TagManagerComponent::TagManagerComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState()),
    mTagBrowser (inMainProcess)
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mNewTagBg, "NewTagBg.svg");
    mImages.setDrawableButtonImages (mBackground, "ModalBgLIGHT.svg");
    mImages.setDrawableButtonImages (mTagBrowserBg, "TagBrowserBg.svg");
    mImages.setDrawableButtonImages (mCreateTagButton, "CreateTag.svg");

    mCreateTagButton.setTriggeredOnMouseDown (true);
    mCreateTagButton.onClick = [this]() { mBrowserState.handleClickCreateTag(); };

    mNewTagInput.setWantsKeyboardFocus (true);
    mNewTagInput.setColour (TextEditor::backgroundColourId, COLOR_TRANSPARENT);
    mNewTagInput.setTextToShowWhenEmpty ("enter tag name...", COLOR_GREY);
    mNewTagInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mNewTagInput.onTextChange = [this]()
    {
        mBrowserState.handleNewTagTextChanged(mNewTagInput.getText());
    };

    mTagViewport.setScrollBarsShown (true, false);
    mTagViewport.setViewedComponent (&mTagBrowser, false);

    addAndMakeVisible (mBackground);
    addAndMakeVisible (mNewTagBg);
    addAndMakeVisible (mNewTagInput);
    addAndMakeVisible (mCreateTagButton);
    addAndMakeVisible (mTagBrowserBg);
    addAndMakeVisible (mTagViewport);
}

TagManagerComponent::~TagManagerComponent()
{
}

//==============================================================================
void TagManagerComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_OVERLAY);
    inGraphics.fillRect (getLocalBounds());

    auto mainArea = getLocalBounds();
    mNewTagBg.setBounds (Styles::getRelativeBounds (mainArea, TAG_INPUT_X, TAG_INPUT_Y, TAG_INPUT_WIDTH, ITEM_HEIGHT));
    mTagBrowserBg.setBounds (Styles::getRelativeBounds (mainArea, TAG_BROWSER_X, TAG_BROWSER_Y, TAG_BROWSER_WIDTH, TAG_BROWSER_HEIGHT));
}

void TagManagerComponent::resized()
{
    auto mainArea = getLocalBounds();
    mBackground.setBounds (Styles::getRelativeBounds (mainArea, MODAL_X, MODAL_Y, MODAL_WIDTH, MODAL_HEIGHT));
    mNewTagInput.setBounds (Styles::getRelativeBounds (mainArea, TAG_INPUT_X, TAG_INPUT_Y, TAG_INPUT_WIDTH, ITEM_HEIGHT));
    mCreateTagButton.setBounds (Styles::getRelativeBounds (mainArea, CREATE_TAG_X, TAG_INPUT_Y, BUTTON_WIDTH, ITEM_HEIGHT));

    int inputHeight = mNewTagInput.getHeight();
    float inputFontHeight = inputHeight * TEXT_INPUT_FONT_HEIGHT_RATIO;

    mNewTagInput.applyFontToAllText (Font (inputFontHeight));
    mNewTagInput.setIndents ((inputHeight * 0.4f), int ((inputHeight - inputFontHeight) * 0.5f));

    mTagViewport.setScrollBarThickness (inputHeight * 0.4f);
    mTagViewport.setBounds (Styles::getRelativeBounds (mainArea, TAG_VIEWPORT_X, TAG_VIEWPORT_Y, TAG_VIEWPORT_WIDTH, TAG_VIEWPORT_HEIGHT));

    auto tagBrowserArea = Styles::getRelativeBounds (mainArea, TAG_BROWSER_X, TAG_BROWSER_Y, TAG_BROWSER_WIDTH, TAG_BROWSER_HEIGHT - 2);
    mTagBrowser.setBounds (tagBrowserArea);
    mTagBrowser.setDimensions (tagBrowserArea.getWidth(), tagBrowserArea.getHeight());
}

//==============================================================================
void TagManagerComponent::mouseDown (const MouseEvent& inEvent)
{
    mBrowserState.toggleTagManager();
}

//==============================================================================
void TagManagerComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleTagManager): { handleToggleTagManager (inMessage); } break;
        case (MessageCode::kTagCreated): { handleTagCreated (inMessage); } break;
        default: { } break;
    };
}

void TagManagerComponent::handleToggleTagManager (const DataMessage* inMessage)
{
    if (!mBrowserState.isTagManagerVisible()) { return; }

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");
}

void TagManagerComponent::handleTagCreated (const DataMessage* inMessage)
{
    mNewTagInput.clear();
}
