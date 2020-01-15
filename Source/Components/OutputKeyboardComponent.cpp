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
        case (MessageCode::kModeUpdated): { handleModeUpdated (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        case (MessageCode::kEditModeInputNote): { handleEditModeOutputNotes (inMessage); } break;
        case (MessageCode::kEditModeOutputNotes): { handleEditModeOutputNotes (inMessage); } break;
        case (MessageCode::kCurrentlyOnOutputNotes): { handleCurrentlyOnOutputNotes (inMessage); } break;
        default: { } break;
    };
}

void OutputKeyboardComponent::handleModeUpdated (const DataMessage* inMessage)
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

void OutputKeyboardComponent::handleCurrentlyOnOutputNotes (const DataMessage* inMessage)
{
    juce::Array<int> prevCurrentlyOnOutputNotes = inMessage->messageArray1;
    juce::Array<int> nextCurrentlyOnOutputNotes = inMessage->messageArray2;

    for (int& outputNote : prevCurrentlyOnOutputNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        keyComponent->setNoteAndMarkerColor (keyComponent->getDefaultColor (outputNote));
    }

    for (int& outputNote : nextCurrentlyOnOutputNotes)
    {
        if (outputNote > OUTPUT_NOTE_MODIFIER)
        {
            auto keyComponent = mKeyComponents.at (outputNote - OUTPUT_NOTE_MODIFIER);
            keyComponent->setNoteAndMarkerColor (COLOR_BLUE_DARK);
        }
        else
        {
            auto keyComponent = mKeyComponents.at (outputNote);
            keyComponent->setNoteAndMarkerColor (COLOR_BLUE);
        }
    }

    for (int& outputNote : mPresetState.getChordNotes (mPresetState.getEditModeInputNote()))
    {
        if (!nextCurrentlyOnOutputNotes.contains (outputNote) &&
            !nextCurrentlyOnOutputNotes.contains (outputNote + OUTPUT_NOTE_MODIFIER))
        {
            auto keyComponent = mKeyComponents.at (outputNote);
            keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
        }
    }
}
