#include "InputKeyboardComponent.h"

//==============================================================================
InputKeyboardComponent::InputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState())
{
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
    DBG("INPUT NOTE UP: " << inNoteNumber);
}

void InputKeyboardComponent::handleMouseDown (const int inNoteNumber)
{
    DBG("INPUT NOTE DOWN: " << inNoteNumber);
}
