#include "OutputKeyboardComponent.h"

//==============================================================================
OutputKeyboardComponent::OutputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

OutputKeyboardComponent::~OutputKeyboardComponent()
{
}

//==============================================================================
void OutputKeyboardComponent::resized()
{
    initKeyboard();

    for (int noteNumber = mFirstKey; noteNumber <= mLastKey; noteNumber++)
    {
        auto keyComponent = mKeyComponents.at (noteNumber);
        keyComponent->onMouseDown = [this](const int inNoteNumber) { handleMouseDown (inNoteNumber); };
    }
}

//==============================================================================
void OutputKeyboardComponent::handleMouseDown (const int inNoteNumber)
{
    if (mGlobalState.isEditMode()) { handleEditModeMouseDown (inNoteNumber); }
}

void OutputKeyboardComponent::handleEditModeMouseDown (const int inNoteNumber)
{

}

//==============================================================================
void OutputKeyboardComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kEditModeInputNote): { handleEditModeInputNote (inMessage); } break;
        case (MessageCode::kEditModeOutputNote): { handleEditModeOutputNote (inMessage); } break;
        default: { } break;
    };
}

void OutputKeyboardComponent::handleEditModeInputNote (const DataMessage* inMessage)
{
    Array<int> prevInputChordNotes = inMessage->messageArray1;
    Array<int> nextInputChordNotes = inMessage->messageArray2;

    for (int& outputNote : prevInputChordNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        auto defaultColor = keyComponent->getDefaultColor (outputNote);

        keyComponent->setNoteColor (defaultColor);
        keyComponent->setMarkerColor (defaultColor);
    }

    for (int& outputNote : nextInputChordNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);

        keyComponent->setNoteColor (COLOR_GREEN);
        keyComponent->setMarkerColor (COLOR_GREEN);
    }
}

void OutputKeyboardComponent::handleEditModeOutputNote (const DataMessage* inMessage)
{

}
