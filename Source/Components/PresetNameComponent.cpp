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

    mImages.setDrawableButtonImages (mLeftArrowButton, "Prev.svg", "", "PrevON.svg", "");
    mImages.setDrawableButtonImages (mRightArrowButton, "Next.svg", "", "NextON.svg", "");

    mLeftArrowButton.setTriggeredOnMouseDown (true);
    mRightArrowButton.setTriggeredOnMouseDown (true);

    mLeftArrowButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mBrowserState.handleMouseDownOnLeftArrow (mPresetState.getName());
    };

    mRightArrowButton.onClick = [this]()
    {
        if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
        mBrowserState.handleMouseDownOnRightArrow (mPresetState.getName());
    };

    mPresetNameLabel.setJustificationType (Justification::centred);

    mPresetNameInput.setTextToShowWhenEmpty ("name this preset...", COLOR_GREY_MEDIUM);
    mPresetNameInput.setColour (TextEditor::backgroundColourId, COLOR_GREY_LIGHTER);
    mPresetNameInput.setJustification (Justification::centred);
    mPresetNameInput.setWantsKeyboardFocus (true);
    mPresetNameInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mPresetNameInput.onTextChange = [this]()
    {
        mPresetState.handlePresetNameTextChanged (mPresetNameInput.getText());
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

    auto& input = mPresetNameInput;
    float extra = input.getHeight() - input.getFont().getHeight() - input.getBorder().getTopAndBottom();
    mPresetNameInput.setIndents (5, (int) (extra * 0.5f));
}

//==============================================================================
void PresetNameComponent::triggerLeftArrow()
{
    mLeftArrowButton.triggerClick();
}

void PresetNameComponent::triggerRightArrow()
{
    mRightArrowButton.triggerClick();
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
    mPresetState.handleMouseDownOnPreset (presetFile);
}
