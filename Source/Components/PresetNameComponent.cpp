#include "PresetNameComponent.h"

//==============================================================================
PresetNameComponent::PresetNameComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mBrowserState (mMainProcess.getBrowserState()),
    mMidiState (mMainProcess.getMidiState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mBrowserState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);

    setWantsKeyboardFocus (true);

    mPresetNameInput.setWantsKeyboardFocus (true);
    mPresetNameInput.setJustification (Justification::centred);
    mPresetNameInput.setTextToShowWhenEmpty ("name this preset...", COLOR_GREY);
    mPresetNameInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mPresetNameInput.onTextChange = [this]()
    {
        mPresetState.handlePresetNameTextChanged (mPresetNameInput.getText());
    };

    mPresetNameLabel.setJustificationType (Justification::centred);

    mImages.setDrawableButtonImages (mLeftArrowButton, "Prev.svg", "", "PrevON.svg", "");
    mImages.setDrawableButtonImages (mRightArrowButton, "Next.svg", "", "NextON.svg", "");

    mLeftArrowButton.setTriggeredOnMouseDown (true);
    mRightArrowButton.setTriggeredOnMouseDown (true);

    mLeftArrowButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mBrowserState.handleClickLeftArrow (mPresetState.getName());
    };

    mRightArrowButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mBrowserState.handleClickRightArrow (mPresetState.getName());
    };

    addAndMakeVisible (mLeftArrowButton);
    addAndMakeVisible (mRightArrowButton);
    addAndMakeVisible (mPresetNameLabel);
    addChildComponent (mPresetNameInput);
}

PresetNameComponent::~PresetNameComponent()
{
}

//==============================================================================
void PresetNameComponent::resized()
{
    auto area = getLocalBounds();
    int arrowWidth = area.proportionOfWidth (ARROW_WIDTH / TEXT_INPUT_WIDTH);
    auto textFont = Font (area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO).boldened();

    mPresetNameInput.setFont (textFont);
    mPresetNameLabel.setFont (textFont);

    mPresetNameInput.setBounds (area);
    mLeftArrowButton.setBounds (area.removeFromLeft (arrowWidth));
    mRightArrowButton.setBounds (area.removeFromRight (arrowWidth));
    mPresetNameLabel.setBounds (area);
    mPresetNameInput.setIndents (5, -1);
}

//==============================================================================
void PresetNameComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetNameTextChanged (inMessage); } break;
        case (MessageCode::kPresetNameTextChanged): { handlePresetNameTextChanged (inMessage); } break;
        case (MessageCode::kCurrentIndexChanged): { handleCurrentIndexChanged (inMessage); } break;
        default: { } break;
    };
}

void PresetNameComponent::handleToggleMode (const DataMessage* inMessage)
{
    const String presetName = mPresetState.getName();
    mPresetNameInput.setVisible (mGlobalState.isEditMode());
    mPresetNameLabel.setVisible (!mGlobalState.isEditMode());
    mLeftArrowButton.setVisible (!mGlobalState.isEditMode());
    mRightArrowButton.setVisible (!mGlobalState.isEditMode());

    if (presetName.isNotEmpty())
    {
        mPresetNameInput.clear();
        mPresetNameInput.setText (presetName);
        mPresetNameLabel.setText (presetName, dontSendNotification);
    }
}

void PresetNameComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    mPresetNameInput.clear();
    mPresetNameLabel.setText ("init", dontSendNotification);
}

void PresetNameComponent::handlePresetNameTextChanged (const DataMessage* inMessage)
{
    String nextPresetName = inMessage->messageVar1;
    mPresetNameLabel.setText (nextPresetName, dontSendNotification);
    mPresetNameInput.setText (nextPresetName);
}

void PresetNameComponent::handleCurrentIndexChanged (const DataMessage* inMessage)
{
    int nextIndex = inMessage->messageVar1;
    if (nextIndex < 0) { return; }

    File presetFile = mBrowserState.getAllPresetFiles()[nextIndex];
    mPresetState.handleClickPreset (presetFile);
}
