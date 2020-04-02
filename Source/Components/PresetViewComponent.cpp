#include "PresetViewComponent.h"

//==============================================================================
PresetViewComponent::PresetViewComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mBrowserState (mMainProcess.getBrowserState()),
    mPresetBrowser (inMainProcess)
{
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mPresetFilterInput.setTextToShowWhenEmpty ("search presets...", COLOR_GREY_MEDIUM);
    mPresetFilterInput.setColour (TextEditor::outlineColourId, COLOR_GREY_LIGHTER);
    mPresetFilterInput.setColour (TextEditor::focusedOutlineColourId, COLOR_BLUE);
    mPresetFilterInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mPresetFilterInput.onTextChange = [this]()
    {
        mBrowserState.handlePresetFilterTextChanged (mPresetFilterInput.getText());
    };

    mImages.setDrawableButtonImages (mFavoritesButton, "Favorites.svg");
    mImages.setDrawableButtonImages (mKeyboardsButton, "Keyboards.svg");

    mFavoritesButton.setTriggeredOnMouseDown (true);
    mFavoritesButton.onClick = [this]() { mBrowserState.handleMouseDownOnFavorites(); };

    mKeyboardsButton.setTriggeredOnMouseDown (true);
    mKeyboardsButton.onClick = [this]() { mGlobalState.toggleView(); };

    mPresetViewport.setScrollBarsShown (true, false);
    mPresetViewport.setViewedComponent (&mPresetBrowser, false);

    addAndMakeVisible (mPresetFilterInput);
    addAndMakeVisible (mPresetViewport);
    addAndMakeVisible (mFavoritesButton);
    addAndMakeVisible (mKeyboardsButton);
}

PresetViewComponent::~PresetViewComponent()
{
}

//==============================================================================
void PresetViewComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY_DARK);
    auto mainArea = getLocalBounds();

    auto presetBrowserBgArea = Styles::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y,
                                                       PRESET_LIST_WIDTH, PRESET_LIST_HEIGHT).toFloat();

    float cornerSize = presetBrowserBgArea.getHeight() * (CORNER_SIZE_RATIO * (ITEM_HEIGHT / PRESET_LIST_HEIGHT));
    inGraphics.fillRoundedRectangle (presetBrowserBgArea, cornerSize);
}

void PresetViewComponent::resized()
{
    auto mainArea = getLocalBounds();

    mPresetFilterInput.setBounds (Styles::getRelativeBounds (mainArea, LEFT_BUTTON_X, OUTPUT_KEYBOARD_BG_Y,
                                                             KEYBOARD_BG_WIDTH, ITEM_HEIGHT));

    mFavoritesButton.setBounds (Styles::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y,
                                                           BUTTON_WIDTH, ITEM_HEIGHT));

    mKeyboardsButton.setBounds (Styles::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y,
                                                           BUTTON_WIDTH, ITEM_HEIGHT));

    int inputHeight = mPresetFilterInput.getHeight();
    float inputFontHeight = inputHeight * TEXT_INPUT_FONT_HEIGHT_RATIO;

    mPresetFilterInput.applyFontToAllText (Font (inputFontHeight));
    mPresetFilterInput.setIndents ((inputHeight * 0.4f), int ((inputHeight - inputFontHeight) * 0.5f));

    int scrollbarWidth = inputHeight * 0.6f;
    mPresetViewport.setScrollBarThickness (scrollbarWidth);

    auto viewportArea = Styles::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y,
                                                   PRESET_VIEWPORT_WIDTH, PRESET_VIEWPORT_HEIGHT);

    auto presetBrowserArea = Styles::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y,
                                                     PRESET_LIST_WIDTH, PRESET_LIST_HEIGHT);

    mPresetViewport.setBounds (viewportArea);
    mPresetBrowser.setBounds (presetBrowserArea);
    mPresetBrowser.setDimensions (presetBrowserArea.getWidth(), presetBrowserArea.getHeight());
}

//==============================================================================
void PresetViewComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleFavorites): { handleToggleFavorites (inMessage); } break;
        case (MessageCode::kPresetFilterTextChanged): { handlePresetFilterTextChanged (inMessage); } break;
        default: { } break;
    };
}

//==============================================================================
void PresetViewComponent::handleToggleFavorites (const DataMessage* inMessage)
{
    bool isFavoritesOn = inMessage->messageVar1;
    mImages.setDrawableButtonImages (mFavoritesButton, isFavoritesOn ? "FavoritesON.svg" : "Favorites.svg");
}

void PresetViewComponent::handlePresetFilterTextChanged (const DataMessage* inMessage)
{
    String filterText = inMessage->messageVar1;
    mPresetFilterInput.setText (filterText, dontSendNotification);
}
