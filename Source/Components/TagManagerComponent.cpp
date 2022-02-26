#include "TagManagerComponent.h"

//==============================================================================
TagManagerComponent::TagManagerComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState())
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");
    mImages.setDrawableButtonImages (mNewTagBg, "SearchBg.svg");
    mImages.setDrawableButtonImages (mCreateTagButton, "CreateTag.svg");

    mCreateTagButton.setTriggeredOnMouseDown (true);
    mCreateTagButton.onClick = [this]() { }; // do stuff

    mNewTagInput.setWantsKeyboardFocus (true);
    mNewTagInput.setColour (TextEditor::backgroundColourId, COLOR_TRANSPARENT);
    mNewTagInput.setTextToShowWhenEmpty ("enter tag name...", COLOR_GREY);
    mNewTagInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mNewTagInput.onTextChange = [this]()
    {
        mBrowserState.handleNewTagTextChanged(mNewTagInput.getText());
    };

    addAndMakeVisible (mBackground);
    addAndMakeVisible (mNewTagBg);
    addAndMakeVisible (mNewTagInput);
    addAndMakeVisible (mCreateTagButton);
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
        default: { } break;
    };
}

void TagManagerComponent::handleToggleTagManager (const DataMessage* inMessage)
{
    if (mBrowserState.isTagManagerHidden()) { return; }

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");
}
