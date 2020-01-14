#include "MenuComponent.h"

//==============================================================================
MenuComponent::MenuComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mImages.setDrawableButtonImages (mNewButton, "New.svg");
    mImages.setDrawableButtonImages (mImportButton, "Import.svg");
    mImages.setDrawableButtonImages (mExportButton, "Export.svg");
    mImages.setDrawableButtonImages (mCommunityButton, "Community.svg");

    mNewButton.setTriggeredOnMouseDown (true);
    mImportButton.setTriggeredOnMouseDown (true);
    mExportButton.setTriggeredOnMouseDown (true);
    mCommunityButton.setTriggeredOnMouseDown (true);

    mNewButton.onClick = [this]()
    {
        mGlobalState.toggleMenu();
        mPresetState.handleMouseClickOnNew();
    };

    mImportButton.onClick = [this]()
    {
        mGlobalState.toggleMenu();
        mPresetState.handleMouseClickOnImport();
    };

    mExportButton.onClick = [this]()
    {
        mGlobalState.toggleMenu();
        mPresetState.handleMouseClickOnExport();
    };

    mCommunityButton.onClick = [this]()
    {
        mGlobalState.toggleMenu();
        URL url { "https://trackbout.com/presets" };
        url.launchInDefaultBrowser();
    };

    addAndMakeVisible (mNewButton);
    addAndMakeVisible (mImportButton);
    addAndMakeVisible (mExportButton);
    addAndMakeVisible (mCommunityButton);
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
    auto menuArea = Styles::getRelativeBounds (mainArea, ACTIONS_MENU_X, ACTIONS_MENU_Y,
                                               ACTIONS_MENU_WIDTH, ACTIONS_MENU_HEIGHT);

    int menuHeight = menuArea.getHeight();
    int buttonHeight = menuHeight / ACTIONS_MENU_BUTTON_COUNT;

    mNewButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mImportButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mExportButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mCommunityButton.setBounds (menuArea.removeFromTop (buttonHeight));
}

//==============================================================================
void MenuComponent::mouseDown (const MouseEvent& inEvent)
{
    if (handleBackgroundClick) { handleBackgroundClick(); }
}
