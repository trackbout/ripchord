#include "PresetViewComponent.h"

//==============================================================================
PresetViewComponent::PresetViewComponent()
{
    mPresetFilterInput.setTextToShowWhenEmpty ("search presets...", COLOR_GREY_MEDIUM);
    mPresetFilterInput.setColour (TextEditor::outlineColourId, COLOR_GREY_LIGHTER);
    mPresetFilterInput.setColour (TextEditor::focusedOutlineColourId, COLOR_BLUE);

    mImages.setDrawableButtonImages (mFavoritesButton, "Favorites.svg", "", "", "", "FavoritesON.svg", "", "", "");
    mImages.setDrawableButtonImages (mKeyboardsButton, "Keyboards.svg");

    mFavoritesButton.setTriggeredOnMouseDown (true);
    mKeyboardsButton.setTriggeredOnMouseDown (true);

    mPresetViewport.setViewedComponent (&mPresetListComponent, false);
    mPresetViewport.setScrollBarsShown (true, false);

    addAndMakeVisible (mFavoritesButton);
    addAndMakeVisible (mKeyboardsButton);
    addAndMakeVisible (mPresetViewport);
}

PresetViewComponent::~PresetViewComponent()
{
}

//==============================================================================
void PresetViewComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_GREY_DARK);
    auto mainArea = getLocalBounds();

    auto presetListBgArea = Interface::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y,
                                                      PRESET_LIST_WIDTH, PRESET_LIST_HEIGHT).toFloat();

    float cornerSize = presetListBgArea.getHeight() * (CORNER_SIZE_RATIO * (ITEM_HEIGHT / PRESET_LIST_HEIGHT));
    inGraphics.fillRoundedRectangle (presetListBgArea, cornerSize);
}

void PresetViewComponent::resized()
{
    auto mainArea = getLocalBounds();

    mPresetFilterInput.setBounds (Interface::getRelativeBounds (mainArea, LEFT_BUTTON_X, OUTPUT_KEYBOARD_BG_Y,
                                                                KEYBOARD_BG_WIDTH, ITEM_HEIGHT));

    mFavoritesButton.setBounds (Interface::getRelativeBounds (mainArea, LEFT_BUTTON_X, FOOTER_Y,
                                                              BUTTON_WIDTH, ITEM_HEIGHT));

    mKeyboardsButton.setBounds (Interface::getRelativeBounds (mainArea, RIGHT_BUTTON_X, FOOTER_Y,
                                                              BUTTON_WIDTH, ITEM_HEIGHT));

    int inputHeight = mPresetFilterInput.getHeight();
    float inputFontHeight = inputHeight * TEXT_INPUT_FONT_HEIGHT_RATIO;
    mPresetFilterInput.applyFontToAllText (Font (inputFontHeight));
    mPresetFilterInput.setIndents ((inputHeight * 0.4f), int ((inputHeight - inputFontHeight) * 0.5f));

    int scrollbarWidth = inputHeight * 0.6f;
    mPresetViewport.setScrollBarThickness (scrollbarWidth);

    auto viewportArea = Interface::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y,
                                                        PRESET_VIEWPORT_WIDTH, PRESET_VIEWPORT_HEIGHT);

    auto presetListArea = Interface::getRelativeBounds (mainArea, SPACE, PRESET_VIEWPORT_Y,
                                                          PRESET_LIST_WIDTH, PRESET_LIST_HEIGHT);

    mPresetViewport.setBounds (viewportArea);
    mPresetListComponent.setBounds (presetListArea);
    mPresetListComponent.setViewedSize (presetListArea.getWidth(), presetListArea.getHeight());
}
