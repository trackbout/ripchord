#include "OutputKeyboardComponent.h"

//==============================================================================
OutputKeyboardComponent::OutputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState())
{
}

OutputKeyboardComponent::~OutputKeyboardComponent()
{
}

//==============================================================================
void OutputKeyboardComponent::resized()
{
    initKeyboard();

    for (auto& keyComponent : mKeyComponents)
    {
        keyComponent->onMouseUp = [this](const int inNoteNumber) { handleMouseUp (inNoteNumber); };
        keyComponent->onMouseDown = [this](const int inNoteNumber) { handleMouseDown (inNoteNumber); };
    }
}

//==============================================================================
void OutputKeyboardComponent::handleMouseUp (const int inNoteNumber)
{
    DBG("OUTPUT NOTE UP: " << inNoteNumber);
}

void OutputKeyboardComponent::handleMouseDown (const int inNoteNumber)
{
    DBG("OUTPUT NOTE DOWN: " << inNoteNumber);
}
