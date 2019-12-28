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
    mPresetState.setEditModeInputNote (inNoteNumber);
}

//==============================================================================
void InputKeyboardComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kEditModeInputNote): { handleEditModeInputNote (inMessage); } break;
        default: { } break;
    };
}

void InputKeyboardComponent::handleEditModeInputNote (const DataMessage* inMessage)
{
    const int prevEditModeInputNote = inMessage->messageVar1;
    const int nextEditModeInputNote = inMessage->messageVar2;

    if (prevEditModeInputNote > 0)
    {
        auto prevKeyComponent = mKeyComponents.at (prevEditModeInputNote);
        auto defaultColor = prevKeyComponent->getDefaultColor (prevEditModeInputNote);

        prevKeyComponent->setNoteColor (defaultColor);
        prevKeyComponent->setMarkerColor (defaultColor);
    }

    if (nextEditModeInputNote > 0)
    {
        auto nextKeyComponent = mKeyComponents.at (nextEditModeInputNote);

        nextKeyComponent->setNoteColor (COLOR_GREEN);
        nextKeyComponent->setMarkerColor (COLOR_GREEN);
    }
}
