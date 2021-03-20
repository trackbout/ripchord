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

    mChordNameInput.setWantsKeyboardFocus (true);
    mChordNameInput.setJustification (Justification::centred);
    mChordNameInput.setTextToShowWhenEmpty ("name this chord...", COLOR_GREY);
    mChordNameInput.onReturnKey = [this]() { grabKeyboardFocus(); };

    mChordNameInput.onTextChange = [this]()
    {
        mPresetState.handleChordNameTextChanged (mChordNameInput.getText());
    };

    mChordNameLabel.setJustificationType (Justification::centred);

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

    mChordNameInput.setIndents (5, -1);
}

//==============================================================================
void ChordNameComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        case (MessageCode::kEditModeInputNote): { handleEditModeInputNote (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handleEditModeOutputNotes (inMessage); } break;
        case (MessageCode::kInputNoteOff): { handleInputNoteOff (inMessage); } break;
        case (MessageCode::kInputNoteOn): { handleInputNoteOn (inMessage); } break;
        default: { } break;
    };
}

void ChordNameComponent::handleToggleMode (const DataMessage* inMessage)
{
    mChordNameLabel.setVisible (true);
    mChordNameInput.setVisible (false);
}

void ChordNameComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    mChordNameInput.clear();
}

void ChordNameComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    mChordNameInput.clear();
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
    const bool isInputVisible = nextEditModeOutputNotes.size() > 0;
    mChordNameLabel.setVisible (!isInputVisible);
    mChordNameInput.setVisible (isInputVisible);
}

void ChordNameComponent::handleInputNoteOff (const DataMessage* inMessage)
{
    for (int& inputNote : mMidiState.getCurrentlyOnInputNotes())
    {
        if (mPresetState.containsChord (inputNote))
        {
            mChordNameLabel.setText (mPresetState.getChordName (inputNote), dontSendNotification);
        }
    }

    if (mMidiState.getCurrentlyOnInputNotes().size() == 0)
    {
        mChordNameLabel.setText ("", dontSendNotification);
    }
}

void ChordNameComponent::handleInputNoteOn (const DataMessage* inMessage)
{
    int inputNote = inMessage->messageVar1;

    if (mPresetState.containsChord (inputNote))
    {
        mChordNameLabel.setText (mPresetState.getChordName (inputNote), dontSendNotification);
    }
}
