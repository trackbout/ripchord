#include "MenuComponent.h"

//==============================================================================
MenuComponent::MenuComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mTitleLabel.setFont (Font().boldened());
    mTitleLabel.setColour (Label::textColourId, COLOR_PURPLE);
    mThemeLabel.setFont (Font().boldened());
    mThemeLabel.setColour (Label::textColourId, COLOR_GREY);
    mCreditsLabel.setColour (Label::textColourId, COLOR_GREY);

    mImages.setDrawableButtonImages (mBackground, "ModalBgLIGHT.svg");
    mImages.setDrawableButtonImages (mThemeButton, "MenuThemeLIGHT.svg");
    mImages.setDrawableButtonImages (mCreditsButton, "Trackbout.svg");
    mImages.setDrawableButtonImages (mNewPresetButton, "MenuNewPreset.svg");
    mImages.setDrawableButtonImages (mDuplicateButton, "MenuDuplicate.svg");
    mImages.setDrawableButtonImages (mImportMidiButton, "MenuImportMidi.svg");
    mImages.setDrawableButtonImages (mExportMidiButton, "MenuExportMidi.svg");
    mImages.setDrawableButtonImages (mImportPresetButton, "MenuImportPreset.svg");
    mImages.setDrawableButtonImages (mExportPresetButton, "MenuExportPreset.svg");
    mImages.setDrawableButtonImages (mSourceCodeButton, "MenuSourceCode.svg");

    mThemeButton.setTriggeredOnMouseDown (true);
    mCreditsButton.setTriggeredOnMouseDown (true);
    mNewPresetButton.setTriggeredOnMouseDown (true);
    mDuplicateButton.setTriggeredOnMouseDown (true);
    mImportMidiButton.setTriggeredOnMouseDown (true);
    mExportMidiButton.setTriggeredOnMouseDown (true);
    mImportPresetButton.setTriggeredOnMouseDown (true);
    mExportPresetButton.setTriggeredOnMouseDown (true);
    mSourceCodeButton.setTriggeredOnMouseDown (true);

    mThemeButton.onClick = [this]()
    {
        mGlobalState.toggleTheme();
    };

    mCreditsButton.onClick = [this]()
    {
        URL url { "https://trackbout.com" };
        url.launchInDefaultBrowser();
        mGlobalState.toggleMenu();
    };

    mNewPresetButton.onClick = [this]()
    {
        mPresetState.handleMouseDownOnNew();
        mGlobalState.toggleMenu();
    };

    mDuplicateButton.onClick = [this]()
    {
        if (!mPresetState.isPresetValid()) { return; }
        mPresetState.handleMouseDownOnDuplicate();
        mGlobalState.toggleMenu();
    };

    mImportMidiButton.onClick = [this]()
    {
        mPresetState.handleMouseDownOnImportMidi();
        mGlobalState.toggleMenu();
    };

    mExportMidiButton.onClick = [this]()
    {
        if (!mPresetState.isPresetValid()) { return; }
        mPresetState.handleMouseDownOnExportMidi();
        mGlobalState.toggleMenu();
    };

    mImportPresetButton.onClick = [this]()
    {
        mPresetState.handleMouseDownOnImportPreset();
        mGlobalState.toggleMenu();
    };

    mExportPresetButton.onClick = [this]()
    {
        if (!mPresetState.isPresetValid()) { return; }
        mPresetState.handleMouseDownOnExportPreset();
        mGlobalState.toggleMenu();
    };

    mSourceCodeButton.onClick = [this]()
    {
        URL url { "https://github.com/trackbout/ripchord" };
        url.launchInDefaultBrowser();
        mGlobalState.toggleMenu();
    };

    addAndMakeVisible (mBackground);
    addAndMakeVisible (mTitleLabel);
    addAndMakeVisible (mThemeLabel);
    addAndMakeVisible (mThemeButton);
    addAndMakeVisible (mCreditsLabel);
    addAndMakeVisible (mCreditsButton);
    addAndMakeVisible (mNewPresetButton);
    addAndMakeVisible (mDuplicateButton);
    addAndMakeVisible (mImportMidiButton);
    addAndMakeVisible (mExportMidiButton);
    addAndMakeVisible (mImportPresetButton);
    addAndMakeVisible (mExportPresetButton);
    addAndMakeVisible (mSourceCodeButton);
}

MenuComponent::~MenuComponent()
{
}

//==============================================================================
void MenuComponent::paint (Graphics& inGraphics)
{
    inGraphics.setColour (COLOR_OVERLAY);
    inGraphics.fillRect (getLocalBounds());
}

void MenuComponent::resized()
{
    auto mainArea = getLocalBounds();
    mBackground.setBounds (Styles::getRelativeBounds (mainArea, MODAL_X, MODAL_Y, MODAL_WIDTH, MODAL_HEIGHT));

    auto titleLabelArea = Styles::getRelativeBounds (mainArea, MODAL_X + 44, MENU_ACTION_Y_01 + 2, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT - 4);
    mTitleLabel.setFont (Font ((float) titleLabelArea.getHeight()).boldened());
    mTitleLabel.setBounds (titleLabelArea);

    auto themeLabelArea = Styles::getRelativeBounds (mainArea, MODAL_X + 64, MENU_ACTION_Y_04 - 30, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT - 6);
    mThemeLabel.setFont (Font ((float) themeLabelArea.getHeight()).boldened());
    mThemeLabel.setBounds (themeLabelArea);

    auto creditsLabelArea = Styles::getRelativeBounds (mainArea, MODAL_X + 46, MENU_ACTION_Y_07 + 12, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT - 12);
    mCreditsLabel.setFont (Font ((float) creditsLabelArea.getHeight()));
    mCreditsLabel.setBounds (creditsLabelArea);

    mThemeButton.setBounds (Styles::getRelativeBounds (mainArea, MODAL_X + 67, MENU_ACTION_Y_04, MENU_TOGGLE_WIDTH, MENU_ITEM_HEIGHT));
    mCreditsButton.setBounds (Styles::getRelativeBounds (mainArea, MODAL_X + 67, MENU_ACTION_Y_07 - 4, 120, 12));

    mNewPresetButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_01, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
    mDuplicateButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_02, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
    mImportMidiButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_03, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
    mExportMidiButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_04, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
    mImportPresetButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_05, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
    mExportPresetButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_06, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
    mSourceCodeButton.setBounds (Styles::getRelativeBounds (mainArea, MENU_ACTION_X, MENU_ACTION_Y_07, MENU_ACTION_WIDTH, MENU_ITEM_HEIGHT));
}

//==============================================================================
void MenuComponent::mouseDown (const MouseEvent& inEvent)
{
    mGlobalState.toggleMenu();
}

//==============================================================================
void MenuComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMenu): { handleToggleMenu (inMessage); } break;
        case (MessageCode::kToggleTheme): { handleToggleTheme (inMessage); } break;
        default: { } break;
    };
}

void MenuComponent::handleToggleMenu (const DataMessage* inMessage)
{
    if (mGlobalState.isMenuHidden()) { return; }

    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");
    mImages.setDrawableButtonImages (mThemeButton, isDark ? "MenuThemeDARK.svg" : "MenuThemeLIGHT.svg");

    bool hasValidPreset = mPresetState.isPresetValid();
    mImages.setDrawableButtonImages (mDuplicateButton, hasValidPreset ? "MenuDuplicate.svg" : "MenuDuplicateOFF.svg");
    mImages.setDrawableButtonImages (mExportMidiButton, hasValidPreset ? "MenuExportMidi.svg" : "MenuExportMidiOFF.svg");
    mImages.setDrawableButtonImages (mExportPresetButton, hasValidPreset ? "MenuExportPreset.svg" : "MenuExportPresetOFF.svg");
}

void MenuComponent::handleToggleTheme (const DataMessage* inMessage)
{
    bool isDark = mGlobalState.isDarkTheme();
    mImages.setDrawableButtonImages (mBackground, isDark ? "ModalBgDARK.svg" : "ModalBgLIGHT.svg");
    mImages.setDrawableButtonImages (mThemeButton, isDark ? "MenuThemeDARK.svg" : "MenuThemeLIGHT.svg");
}
