#include "OutputKeyboardComponent.h"

//==============================================================================
OutputKeyboardComponent::OutputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState()),
    mMidiState (mMainProcess.getMidiState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mMidiState.DataMessageBroadcaster::addListener (this, ListenerType::kAsync);
}

OutputKeyboardComponent::~OutputKeyboardComponent()
{
}

//==============================================================================
void OutputKeyboardComponent::resized()
{
    initKeyboard();

    for (int outputNote = mFirstKey; outputNote <= mLastKey; outputNote++)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        keyComponent->onMouseDown = [this](const int inOutputNote) { handleMouseDown (inOutputNote); };
    }
}

//==============================================================================
void OutputKeyboardComponent::handleMouseDown (const int inOutputNote)
{
    if (mGlobalState.isEditMode()) { mPresetState.handleEditModeMouseDownOnOutput (inOutputNote); }
}

//==============================================================================
void OutputKeyboardComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        case (MessageCode::kResetOutputKeyboard): { handleResetOutputKeyboard (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handleEditModeOutputNotes (inMessage); } break;
        case (MessageCode::kEditModeInputNote): { handleEditModeOutputNotes (inMessage); } break;
        case (MessageCode::kOutputNoteOff): { handleOutputNoteOff (inMessage); } break;
        case (MessageCode::kOutputNoteOn): { handleOutputNoteOn (inMessage); } break;
        default: { } break;
    };
}

void OutputKeyboardComponent::handleToggleMode (const DataMessage* inMessage)
{
    resetKeyColors();
}

void OutputKeyboardComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    resetKeyColors();
}

void OutputKeyboardComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    resetKeyColors();
}

void OutputKeyboardComponent::handleResetOutputKeyboard (const DataMessage* inMessage)
{
    resetKeyColors();
}

void OutputKeyboardComponent::handleEditModeOutputNotes (const DataMessage* inMessage)
{
    juce::Array<int> prevEditModeOutputNotes = inMessage->messageArray1;
    juce::Array<int> nextEditModeOutputNotes = inMessage->messageArray2;

    for (int& outputNote : prevEditModeOutputNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        keyComponent->setNoteAndMarkerColor (keyComponent->getDefaultColor (outputNote));
    }

    for (int& outputNote : nextEditModeOutputNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
    }
}

void OutputKeyboardComponent::handleOutputNoteOff (const DataMessage* inMessage)
{
    int outputNote = inMessage->messageVar1;
    juce::Array<int> triggers = inMessage->messageArray1;

    auto keyComponent = mKeyComponents.at (outputNote);
    keyComponent->setNoteAndMarkerColor (triggers.size() == 1 ? COLOR_BLUE : keyComponent->getDefaultColor (outputNote));

    if (mGlobalState.isEditMode())
    {
        juce::Array<int> chordNotes = mPresetState.getChordNotes (mPresetState.getEditModeInputNote());
        if (chordNotes.contains (outputNote)) { keyComponent->setNoteAndMarkerColor (COLOR_GREEN); }
    }
}

void OutputKeyboardComponent::handleOutputNoteOn (const DataMessage* inMessage)
{
    int outputNote = inMessage->messageVar1;
    juce::Array<int> triggers = inMessage->messageArray1;

    auto keyComponent = mKeyComponents.at (outputNote);
    keyComponent->setNoteAndMarkerColor (triggers.size() == 2 ? COLOR_BLUE_DARK : COLOR_BLUE);
}
