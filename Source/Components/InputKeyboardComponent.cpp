#include "InputKeyboardComponent.h"

//==============================================================================
InputKeyboardComponent::InputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mPresetState (mMainProcess.getPresetState())
{
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

InputKeyboardComponent::~InputKeyboardComponent()
{
}

//==============================================================================
void InputKeyboardComponent::resized()
{
    initKeyboard();

    for (int noteNumber = mFirstKey; noteNumber <= mLastKey; noteNumber++)
    {
        auto keyComponent = mKeyComponents.at (noteNumber);
        keyComponent->onMouseUp = [this](const int inNoteNumber) { handleMouseUp (inNoteNumber); };
        keyComponent->onMouseDown = [this](const int inNoteNumber) { handleMouseDown (inNoteNumber); };
    }
}

//==============================================================================
void InputKeyboardComponent::handleMouseUp (const int inNoteNumber)
{
    if (mGlobalState.isPlayMode()) { handlePlayModeMouseUp (inNoteNumber); }
    if (mGlobalState.isEditMode()) { handleEditModeMouseUp (inNoteNumber); }
}

void InputKeyboardComponent::handleMouseDown (const int inNoteNumber)
{
    if (mGlobalState.isPlayMode()) { handlePlayModeMouseDown (inNoteNumber); }
    if (mGlobalState.isEditMode()) { handleEditModeMouseDown (inNoteNumber); }
}

//==============================================================================
void InputKeyboardComponent::handlePlayModeMouseUp (const int inNoteNumber)
{

}

void InputKeyboardComponent::handlePlayModeMouseDown (const int inNoteNumber)
{

}

//==============================================================================
void InputKeyboardComponent::handleEditModeMouseUp (const int inNoteNumber)
{

}

void InputKeyboardComponent::handleEditModeMouseDown (const int inNoteNumber)
{
    mPresetState.setSelectedEditNote (inNoteNumber);
}

//==============================================================================
void InputKeyboardComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kSelectedEditNote): { handleSelectedEditNote (inMessage); } break;
        default: { } break;
    };
}

void InputKeyboardComponent::handleSelectedEditNote (const DataMessage* inMessage)
{
    const int prevSelectedEditNote = inMessage->messageData0;
    const int nextSelectedEditNote = inMessage->messageData1;

    if (prevSelectedEditNote > 0)
    {
        auto prevKeyComponent = mKeyComponents.at (prevSelectedEditNote);
        auto defaultColor = prevKeyComponent->getDefaultColor (prevSelectedEditNote);

        prevKeyComponent->setNoteColor (defaultColor);
        prevKeyComponent->setMarkerColor (defaultColor);
    }

    if (nextSelectedEditNote > 0)
    {
        auto nextKeyComponent = mKeyComponents.at (nextSelectedEditNote);

        nextKeyComponent->setNoteColor (COLOR_GREEN);
        nextKeyComponent->setMarkerColor (COLOR_GREEN);
    }
}
