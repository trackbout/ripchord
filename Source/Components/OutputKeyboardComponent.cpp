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

    for (int outputNote = mFirstKey; outputNote <= mLastKey; outputNote++)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        keyComponent->onMouseDown = [this](const int inOutputNote) { handleMouseDown (inOutputNote); };
    }
}

//==============================================================================
void OutputKeyboardComponent::handleMouseDown (const int inOutputNote)
{

}

//==============================================================================
void OutputKeyboardComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kEditModeInputNote): { handleEditModeInputNote (inMessage); } break;
        default: { } break;
    };
}

void OutputKeyboardComponent::handleEditModeInputNote (const DataMessage* inMessage)
{
    Array<int> prevEditModeOutputNotes = inMessage->messageArray1;
    Array<int> nextEditModeOutputNotes = inMessage->messageArray2;

    for (int& outputNote : prevEditModeOutputNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);
        auto defaultColor = keyComponent->getDefaultColor (outputNote);

        keyComponent->setNoteColor (defaultColor);
        keyComponent->setMarkerColor (defaultColor);
    }

    for (int& outputNote : nextEditModeOutputNotes)
    {
        auto keyComponent = mKeyComponents.at (outputNote);

        keyComponent->setNoteColor (COLOR_GREEN);
        keyComponent->setMarkerColor (COLOR_GREEN);
    }
}

void OutputKeyboardComponent::handleEditModeOutputNotes (const DataMessage* inMessage)
{

}
