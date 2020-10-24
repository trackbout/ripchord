#include "MenuComponent.h"

//==============================================================================
MenuComponent::MenuComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    mImages.setDrawableButtonImages (mNewButton, "New.svg");
    mImages.setDrawableButtonImages (mDuplicateButton, "Duplicate.svg");
    mImages.setDrawableButtonImages (mImportMidiButton, "ImportMidi.svg");
    mImages.setDrawableButtonImages (mExportMidiButton, "ExportMidi.svg");
    mImages.setDrawableButtonImages (mImportPresetButton, "ImportPreset.svg");
    mImages.setDrawableButtonImages (mExportPresetButton, "ExportPreset.svg");
    mImages.setDrawableButtonImages (mCommunityButton, "Community.svg");
    mImages.setDrawableButtonImages (mFooter, "Footer.svg");

    mNewButton.setTriggeredOnMouseDown (true);
    mDuplicateButton.setTriggeredOnMouseDown (true);
    mImportMidiButton.setTriggeredOnMouseDown (true);
    mExportMidiButton.setTriggeredOnMouseDown (true);
    mImportPresetButton.setTriggeredOnMouseDown (true);
    mExportPresetButton.setTriggeredOnMouseDown (true);
    mCommunityButton.setTriggeredOnMouseDown (true);

    mNewButton.onClick = [this]()
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

    mCommunityButton.onClick = [this]()
    {
        URL url { "https://trackbout.com/presets" };
        url.launchInDefaultBrowser();
        mGlobalState.toggleMenu();
    };

    addAndMakeVisible (mNewButton);
    addAndMakeVisible (mDuplicateButton);
    addAndMakeVisible (mImportMidiButton);
    addAndMakeVisible (mExportMidiButton);
    addAndMakeVisible (mImportPresetButton);
    addAndMakeVisible (mExportPresetButton);
    addAndMakeVisible (mCommunityButton);
    addAndMakeVisible (mFooter);
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
    auto menuArea = Styles::getRelativeBounds (mainArea, GEAR_MENU_X, GEAR_MENU_Y,
                                               GEAR_MENU_WIDTH, GEAR_MENU_HEIGHT);

    int menuHeight = menuArea.getHeight();
    int buttonHeight = menuHeight / GEAR_MENU_BUTTON_COUNT;

    mNewButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mDuplicateButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mImportMidiButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mExportMidiButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mImportPresetButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mExportPresetButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mCommunityButton.setBounds (menuArea.removeFromTop (buttonHeight));
    mFooter.setBounds (menuArea.removeFromTop (buttonHeight));
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
    bool hasValidPreset = mPresetState.isPresetValid();
    mImages.setDrawableButtonImages (mDuplicateButton, hasValidPreset ? "Duplicate.svg" : "DuplicateOFF.svg");
    mImages.setDrawableButtonImages (mExportMidiButton, hasValidPreset ? "ExportMidi.svg" : "ExportMidiOFF.svg");
    mImages.setDrawableButtonImages (mExportPresetButton, hasValidPreset ? "ExportPreset.svg" : "ExportPresetOFF.svg");
}
