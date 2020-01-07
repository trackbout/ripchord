#include "ChordNameComponent.h"

//==============================================================================
ChordNameComponent::ChordNameComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mMidiState (mMainProcess.getMidiState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mMidiState.DataMessageBroadcaster::addListener (this, ListenerType::kAsync);

    setWantsKeyboardFocus (true);

    mChordNameLabel.setJustificationType (Justification::centred);

    mChordNameInput.setTextToShowWhenEmpty ("name this chord...", COLOR_GREY_MEDIUM);
    mChordNameInput.setJustification (Justification::centred);
    mChordNameInput.setColour (TextEditor::backgroundColourId, COLOR_GREY_LIGHTER);
    mChordNameInput.setWantsKeyboardFocus (true);
    mChordNameInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mChordNameInput.onTextChange = [this]()
    {
        mPresetState.handleChordNameTextChanged (mChordNameInput.getText());
    };

    addAndMakeVisible (mChordNameLabel);
    addChildComponent (mChordNameInput);
}

ChordNameComponent::~ChordNameComponent()
{
}

//==============================================================================
void ChordNameComponent::resized()
{
    auto area = getLocalBounds();
    auto textFont = Font (area.getHeight() * TEXT_INPUT_FONT_HEIGHT_RATIO).boldened();

    mChordNameLabel.setFont (textFont);
    mChordNameInput.setFont (textFont);

    mChordNameLabel.setBounds (area);
    mChordNameInput.setBounds (area);

    auto& input = mChordNameInput;
    float extra = input.getHeight() - input.getFont().getHeight() - input.getBorder().getTopAndBottom();
    mChordNameInput.setIndents (5, (int) (extra * 0.5f));
}

//==============================================================================
void ChordNameComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kModeUpdated): { handleModeUpdated (inMessage); } break;
        case (MessageCode::kEditModeInputNote): { handleEditModeInputNote (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handleEditModeOutputNotes (inMessage); } break;
        case (MessageCode::kCurrentlyOnInputNotes): { handleCurrentlyOnInputNotes (inMessage); } break;
        default: { } break;
    };
}

void ChordNameComponent::handleModeUpdated (const DataMessage* inMessage)
{
    mChordNameLabel.setVisible (mGlobalState.isPlayMode());
    mChordNameInput.setVisible (false);
}

void ChordNameComponent::handleEditModeInputNote (const DataMessage* inMessage)
{
    const int nextEditModeInputNote = inMessage->messageVar2;
    mChordNameInput.setText (mPresetState.getChordName (nextEditModeInputNote));
    handleEditModeOutputNotes (inMessage);
}

void ChordNameComponent::handleEditModeOutputNotes (const DataMessage* inMessage)
{
    juce::Array<int> nextEditModeOutputNotes = inMessage->messageArray2;
    mChordNameInput.setVisible (nextEditModeOutputNotes.size() > 0);
}

void ChordNameComponent::handleCurrentlyOnInputNotes (const DataMessage* inMessage)
{
    if (mGlobalState.isEditMode()) { return; }

    juce::Array<int> nextCurrentlyOnInputNotes = inMessage->messageArray2;

    for (int& inputNote : nextCurrentlyOnInputNotes)
    {
        if (mPresetState.containsChord (inputNote))
        {
            mChordNameLabel.setText (mPresetState.getChordName (inputNote), dontSendNotification);
        }
    }

    if (nextCurrentlyOnInputNotes.size() == 0)
    {
        mChordNameLabel.setText("", dontSendNotification);
    }
}
