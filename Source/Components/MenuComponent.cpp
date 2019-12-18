#include "MenuComponent.h"

//==============================================================================
MenuComponent::MenuComponent()
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
        DBG("NEW BUTTON");
    };

    mImportButton.onClick = [this]()
    {
        DBG("IMPORT BUTTON");
    };

    mExportButton.onClick = [this]()
    {
        DBG("EXPORT BUTTON");
    };

    mCommunityButton.onClick = [this]()
    {
        DBG("COMMUNITY BUTTON");
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
    auto menuArea = Interface::getRelativeBounds (mainArea, ACTIONS_MENU_X, ACTIONS_MENU_Y,
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
