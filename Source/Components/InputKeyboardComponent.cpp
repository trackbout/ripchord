#include "InputKeyboardComponent.h"

//==============================================================================
InputKeyboardComponent::InputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mInputKeyboardState (mMainProcess.getInputKeyboardState()),
    mCurrentPresetState (mMainProcess.getCurrentPresetState())
{
    mInputKeyboardState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
}

InputKeyboardComponent::~InputKeyboardComponent()
{
}

//==============================================================================
void InputKeyboardComponent::resized()
{
    initKeyboard();

    for (auto& keyComponent : mKeyComponents)
    {
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
    mInputKeyboardState.setSelectedEditNote (inNoteNumber);
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

    auto prevKeyComponent = mKeyComponents[prevSelectedEditNote];
    auto nextKeyComponent = mKeyComponents[nextSelectedEditNote];

    if (prevSelectedEditNote > 0)
    {
        prevKeyComponent->setNoteColor (prevKeyComponent->getDefaultColor (prevSelectedEditNote));
    }

    if (nextSelectedEditNote == 0)
    {
        nextKeyComponent->setNoteColor (nextKeyComponent->getDefaultColor (nextSelectedEditNote));
    }

    if (nextSelectedEditNote > 0)
    {
        nextKeyComponent->setNoteColor (COLOR_GREEN);
    }
}
