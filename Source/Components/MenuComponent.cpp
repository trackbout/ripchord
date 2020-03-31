#include "MenuComponent.h"

//==============================================================================
MenuComponent::MenuComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mNewButton, "New.svg");
    mImages.setDrawableButtonImages (mMidiButton, "MIDI.svg");
    mImages.setDrawableButtonImages (mImportButton, "Import.svg");
    mImages.setDrawableButtonImages (mExportButton, "Export.svg");
    mImages.setDrawableButtonImages (mCommunityButton, "Community.svg");

    mNewButton.setTriggeredOnMouseDown (true);
    mMidiButton.setTriggeredOnMouseDown (true);
    mImportButton.setTriggeredOnMouseDown (true);
    mExportButton.setTriggeredOnMouseDown (true);
    mCommunityButton.setTriggeredOnMouseDown (true);

    mNewButton.onClick = [this]()
    {
        mPresetState.handleMouseClickOnNew();
        mGlobalState.toggleMenu();
    };

    mMidiButton.onClick = [this]()
    {
        mPresetState.handleMouseClickOnMidi();
        mGlobalState.toggleMenu();
    };

    mImportButton.onClick = [this]()
    {
        mPresetState.handleMouseClickOnImport();
        mGlobalState.toggleMenu();
    };

    mExportButton.onClick = [this]()
    {
        if (!mPresetState.isPresetValid()) { return; }
        mPresetState.handleMouseClickOnExport();
        mGlobalState.toggleMenu();
    };

    mCommunityButton.onClick = [this]()
    {
        URL url { "https://trackbout.com/presets" };
        url.launchInDefaultBrowser();
        mGlobalState.toggleMenu();
    };

    addAndMakeVisible (mNewButton);
    addAndMakeVisible (mMidiButton);
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
    mMidiButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mImportButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mExportButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mCommunityButton.setBounds (menuArea.removeFromTop (buttonHeight));
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
        default: { } break;
    };
}

void MenuComponent::handleToggleMenu (const DataMessage* inMessage)
{
    if (mGlobalState.isMenuHidden()) { return; }
    bool isExportable = mPresetState.isPresetValid();
    mImages.setDrawableButtonImages (mExportButton, isExportable ? "Export.svg" : "ExportOFF.svg");
}
