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
    bool prevInputContainsChord = inMessage->messageVar3;
    bool nextInputContainsChord = inMessage->messageVar4;
    Array<int> prevInputChordNotes = inMessage->messageArray1;
    Array<int> nextInputChordNotes = inMessage->messageArray2;

    if (prevInputContainsChord)
    {
        for (int& chordNote : prevInputChordNotes)
        {
            auto keyComponent = mKeyComponents.at (chordNote);
            auto defaultColor = keyComponent->getDefaultColor (chordNote);

            keyComponent->setNoteColor (defaultColor);
            keyComponent->setMarkerColor (defaultColor);
        }
    }

    if (nextInputContainsChord)
    {
        for (int& chordNote : nextInputChordNotes)
        {
            auto keyComponent = mKeyComponents.at (chordNote);

            keyComponent->setNoteColor (COLOR_GREEN);
            keyComponent->setMarkerColor (COLOR_GREEN);
        }
    }
}
