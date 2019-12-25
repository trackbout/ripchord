#include "OutputKeyboardComponent.h"

//==============================================================================
OutputKeyboardComponent::OutputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mCurrentPresetState (mMainProcess.getCurrentPresetState())
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
    if (mGlobalState.isPlayMode()) { handlePlayModeMouseUp (inNoteNumber); }
    if (mGlobalState.isEditMode()) { handleEditModeMouseUp (inNoteNumber); }
}

void OutputKeyboardComponent::handleMouseDown (const int inNoteNumber)
{
    if (mGlobalState.isPlayMode()) { handlePlayModeMouseDown (inNoteNumber); }
    if (mGlobalState.isEditMode()) { handleEditModeMouseDown (inNoteNumber); }
}

//==============================================================================
void OutputKeyboardComponent::handlePlayModeMouseUp (const int inNoteNumber)
{

}

void OutputKeyboardComponent::handlePlayModeMouseDown (const int inNoteNumber)
{

}

//==============================================================================
void OutputKeyboardComponent::handleEditModeMouseUp (const int inNoteNumber)
{

}

void OutputKeyboardComponent::handleEditModeMouseDown (const int inNoteNumber)
{

}
