#include "PresetViewComponent.h"

//==============================================================================
PresetViewComponent::PresetViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState()),
    mTagManager (inMainProcess),
    mPresetBrowser (inMainProcess)
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    bool isSelectorOn = mBrowserState.isTagSelectorOn();

    mImages.setDrawableButtonImages (mTagsBg, "TagsBg.svg");
    mImages.setDrawableButtonImages (mPresetBg, "PresetBg.svg");
    mImages.setDrawableButtonImages (mSearchBg, "SearchBg.svg");
    mImages.setDrawableButtonImages (mMenuButton, "GearCircle.svg");
    mImages.setDrawableButtonImages (mPowerButton, "PowerON.svg");
    mImages.setDrawableButtonImages (mTagManagerButton, "TagManager.svg");
    mImages.setDrawableButtonImages (mTagSelectorButton, isSelectorOn ? "TagSelectorON.svg" : "TagSelector.svg");
    mImages.setDrawableButtonImages (mFavoritesButton, "Favorites.svg");
    mImages.setDrawableButtonImages (mKeyboardsButton, "Keyboards.svg");

    mMenuButton.setTriggeredOnMouseDown (true);
    mMenuButton.onClick = [this]() { mGlobalState.toggleMenu(); };

    mTagManagerButton.setTriggeredOnMouseDown (true);
    mTagManagerButton.onClick = [this]() { mBrowserState.toggleTagManager(); };

    mTagSelectorButton.setTriggeredOnMouseDown (true);
    mTagSelectorButton.onClick = [this]() { mBrowserState.toggleTagSelector(); };

    mFavoritesButton.setTriggeredOnMouseDown (true);
    mFavoritesButton.onClick = [this]() { mBrowserState.toggleFavorites(); };

    mKeyboardsButton.setTriggeredOnMouseDown (true);
    mKeyboardsButton.onClick = [this]() { mGlobalState.toggleView(); };

    mPresetViewport.setScrollBarsShown (true, false);
    mPresetViewport.setViewedComponent (&mPresetBrowser, false);

    mPresetFilterInput.setWantsKeyboardFocus (true);
    mPresetFilterInput.setColour (TextEditor::backgroundColourId, COLOR_TRANSPARENT);
    mPresetFilterInput.setTextToShowWhenEmpty ("search presets...", COLOR_GREY);
    mPresetFilterInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mPresetFilterInput.onTextChange = [this]()
    {
        mBrowserState.handlePresetFilterTextChanged (mPresetFilterInput.getText());
    };

    addAndMakeVisible (mTagsBg);
    addAndMakeVisible (mPresetBg);
    addAndMakeVisible (mSearchBg);
    addAndMakeVisible (mMenuButton);
    addAndMakeVisible (mPowerButton);
    addAndMakeVisible (mTagManagerButton);
    addAndMakeVisible (mTagSelectorButton);
    addAndMakeVisible (mFavoritesButton);
    addAndMakeVisible (mKeyboardsButton);
    addAndMakeVisible (mPresetViewport);
    addAndMakeVisible (mPresetFilterInput);
    addChildComponent (mTagManager);
}

PresetViewComponent::~PresetViewComponent()
{
}

//==============================================================================
void PresetViewComponent::paint (Graphics& inGraphics)
{
    auto mainArea = getLocalBounds();
    mTagsBg.setBounds (Styles::getRelativeBounds (mainArea, TAGS_BG_X, OUTPUT_KEYBOARD_BG_Y, TAGS_BG_WIDTH, ITEM_HEIGHT));
    mPresetBg.setBounds (Styles::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y, KEYBOARD_BG_WIDTH, PRESET_LIST_HEIGHT));
    mSearchBg.setBounds (Styles::getRelativeBounds (mainArea, TEXT_INPUT_X, FOOTER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT));
}

void PresetViewComponent::resized()
{
    auto mainArea = getLocalBounds();

    mTagManager.setBounds (mainArea);
    mMenuButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_BUTTON_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mPowerButton.setBounds (Styles::getRelativeBounds (mainArea, POWER_BUTTON_X, HEADER_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mTagManagerButton.setBounds (Styles::getRelativeBounds (mainArea, TAG_MANAGER_X, OUTPUT_KEYBOARD_BG_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mTagSelectorButton.setBounds (Styles::getRelativeBounds (mainArea, TAG_SELECTOR_X, OUTPUT_KEYBOARD_BG_Y, ITEM_HEIGHT, ITEM_HEIGHT));
    mFavoritesButton.setBounds (Styles::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mKeyboardsButton.setBounds (Styles::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y, BUTTON_WIDTH, ITEM_HEIGHT));
    mPresetFilterInput.setBounds (Styles::getRelativeBounds (mainArea, TEXT_INPUT_X, FOOTER_Y, TEXT_INPUT_WIDTH, ITEM_HEIGHT));

    int inputHeight = mPresetFilterInput.getHeight();
    float inputFontHeight = inputHeight * TEXT_INPUT_FONT_HEIGHT_RATIO;

    mPresetFilterInput.applyFontToAllText (Font (inputFontHeight));
    mPresetFilterInput.setIndents ((inputHeight * 0.4f), int ((inputHeight - inputFontHeight) * 0.5f));

    int scrollbarWidth = inputHeight * 0.6f;
    mPresetViewport.setScrollBarThickness (scrollbarWidth);

    auto viewportArea = Styles::getRelativeBounds (mainArea, SPACE + 1, PRESET_VIEWPORT_Y + 1, PRESET_VIEWPORT_WIDTH - 2, PRESET_VIEWPORT_HEIGHT - 2);
    mPresetViewport.setBounds (viewportArea);

    auto presetArea = Styles::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y, PRESET_LIST_WIDTH, PRESET_LIST_HEIGHT);
    mPresetBrowser.setBounds (presetArea);
    mPresetBrowser.setDimensions (presetArea.getWidth(), presetArea.getHeight());
}

//==============================================================================
void PresetViewComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleView): { handleToggleView (inMessage); } break;
        case (MessageCode::kToggleFavorites): { handleToggleFavorites (inMessage); } break;
        case (MessageCode::kToggleTagManager): { handleToggleTagManager (inMessage); } break;
        case (MessageCode::kToggleTagSelector): { handleToggleTagSelector (inMessage); } break;
        case (MessageCode::kPresetFilterTextChanged): { handlePresetFilterTextChanged (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetViewComponent::handleToggleView (const DataMessage* inMessage)
{
    mImages.setDrawableButtonImages (mPowerButton, mGlobalState.isPowerOn() ? "PowerON.svg" : "Power.svg");
}

void PresetViewComponent::handleToggleFavorites (const DataMessage* inMessage)
{
    bool isFavoritesOn = mBrowserState.isFavoritesOn();
    mImages.setDrawableButtonImages (mFavoritesButton, isFavoritesOn ? "FavoritesON.svg" : "Favorites.svg");
}

void PresetViewComponent::handleToggleTagManager (const DataMessage* inMessage)
{
    mTagManager.setVisible (mBrowserState.isTagManagerVisible());
}

void PresetViewComponent::handleToggleTagSelector (const DataMessage* inMessage)
{
    bool isSelectorOn = mBrowserState.isTagSelectorOn();
    mImages.setDrawableButtonImages (mTagSelectorButton, isSelectorOn ? "TagSelectorON.svg" : "TagSelector.svg");
}

void PresetViewComponent::handlePresetFilterTextChanged (const DataMessage* inMessage)
{
    String filterText = inMessage->messageVar1;
    mPresetFilterInput.setText (filterText, dontSendNotification);
}
