#include "InputKeyboardComponent.h"

//==============================================================================
InputKeyboardComponent::InputKeyboardComponent (MainProcess& inMainProcess)
:   mMainProcess (inMainProcess),
    mGlobalState (mMainProcess.getGlobalState()),
    mControlsState (mMainProcess.getControlsState()),
    mPresetState (mMainProcess.getPresetState()),
    mMidiState (mMainProcess.getMidiState())
{
    mGlobalState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mMidiState.DataMessageBroadcaster::addListener (this, ListenerType::kAsync);
}

InputKeyboardComponent::~InputKeyboardComponent()
{
}

//==============================================================================
void InputKeyboardComponent::resized()
{
    initKeyboard();

    for (int inputNote = mFirstKey; inputNote <= mLastKey; inputNote++)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->onMouseUp = [this](const int inInputNote) { handleMouseUp (inInputNote); };
        keyComponent->onMouseDown = [this](const int inInputNote) { handleMouseDown (inInputNote); };
    }
}

//==============================================================================
void InputKeyboardComponent::handleMouseUp (const int inInputNote)
{
    if (mGlobalState.isPlayMode()) { mMainProcess.handlePlayModeMouseUpOnInput (inInputNote); }
}

void InputKeyboardComponent::handleMouseDown (const int inInputNote)
{
    if (mGlobalState.isPlayMode()) { mMainProcess.handlePlayModeMouseDownOnInput (inInputNote); }
    if (mGlobalState.isEditMode()) { mPresetState.handleEditModeMouseDownOnInput (inInputNote); }
}

//==============================================================================
void InputKeyboardComponent::handleNewMessage (const DataMessage* inMessage)
{
    switch (inMessage->messageCode)
    {
        case (MessageCode::kToggleMode): { handleToggleMode (inMessage); } break;
        case (MessageCode::kPresetFileNew): { handlePresetFileNew (inMessage); } break;
        case (MessageCode::kPresetFileLoaded): { handlePresetFileLoaded (inMessage); } break;
        case (MessageCode::kEditModeInputNote): { handleEditModeInputNote (inMessage); } break;
        case (MessageCode::kCurrentlyOnInputNotes): { handleCurrentlyOnInputNotes (inMessage); } break;
        case (MessageCode::kCurrentlyOnTransposeNote): { handleCurrentlyOnTransposeNote (inMessage); } break;
        case (MessageCode::kTransposeBaseChanged): { handleTransposeBaseChanged (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        default: { } break;
    };
}

void InputKeyboardComponent::handleToggleMode (const DataMessage* inMessage)
{
    const int editModeInputNote = mPresetState.getEditModeInputNote();
    juce::Array<int> presetInputNotes = mPresetState.getPresetInputNotes();
    Colour markerColor = mGlobalState.isEditMode() ? COLOR_GREEN : COLOR_BLUE;

    if (editModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (editModeInputNote);
        keyComponent->setNoteAndMarkerColor (keyComponent->getDefaultColor (editModeInputNote));
        mPresetState.resetEditModeInputNote();
    }

    for (int& inputNote : presetInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->setNoteColor (keyComponent->getDefaultColor (inputNote));
        keyComponent->setMarkerColor (markerColor);
    }
}

void InputKeyboardComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    resetKeyColors();

    if (!mControlsState.isTransposeOff())
    {
        turnOnTransposeKeys (mControlsState.getTransposeBase());
    }
}

void InputKeyboardComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    resetKeyColors();
    juce::Array<int> presetInputNotes = inMessage->messageArray1;

    for (int& inputNote : presetInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->setMarkerColor (COLOR_BLUE);
    }

    if (!mControlsState.isTransposeOff())
    {
        turnOnTransposeKeys (mControlsState.getTransposeBase());
    }
}

void InputKeyboardComponent::handleEditModeInputNote (const DataMessage* inMessage)
{
    const int prevEditModeInputNote = inMessage->messageVar1;
    const int nextEditModeInputNote = inMessage->messageVar2;
    bool prevEditModeInputNoteContainsChord = inMessage->messageVar3;

    if (prevEditModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (prevEditModeInputNote);
        auto defaultColor = keyComponent->getDefaultColor (prevEditModeInputNote);

        if (prevEditModeInputNoteContainsChord) { keyComponent->setNoteColor (defaultColor); }
        else { keyComponent->setNoteAndMarkerColor (defaultColor); }
    }

    if (nextEditModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (nextEditModeInputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
    }
}

void InputKeyboardComponent::handleCurrentlyOnInputNotes (const DataMessage* inMessage)
{
    juce::Array<int> prevCurrentlyOnInputNotes = inMessage->messageArray1;
    juce::Array<int> nextCurrentlyOnInputNotes = inMessage->messageArray2;
    juce::Array<int> presetInputNotes = mPresetState.getPresetInputNotes();
    const int editModeInputNote = mPresetState.getEditModeInputNote();

    for (int& inputNote : prevCurrentlyOnInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        bool containsChord = presetInputNotes.contains (inputNote);
        Colour defaultColor = keyComponent->getDefaultColor (inputNote);
        Colour markerColor = mGlobalState.isEditMode() ? COLOR_GREEN : COLOR_BLUE;
        keyComponent->setNoteColor (keyComponent->getDefaultColor (inputNote));
        keyComponent->setMarkerColor (containsChord ? markerColor : defaultColor);
    }

    for (int& inputNote : nextCurrentlyOnInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_BLUE);
    }

    if (!nextCurrentlyOnInputNotes.contains (editModeInputNote) && editModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (editModeInputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
    }
}

void InputKeyboardComponent::handleCurrentlyOnTransposeNote (const DataMessage* inMessage)
{
    const int prevTransposeNote = inMessage->messageVar1;
    const int nextTransposeNote = inMessage->messageVar2;

    if (mControlsState.isTransposeOn())
    {
        if (nextTransposeNote == -1)
        {
            auto keyComponent = mKeyComponents.at (prevTransposeNote);
            keyComponent->setNoteColor (keyComponent->getDefaultColor (prevTransposeNote));
        }

        if (nextTransposeNote > 0)
        {
            auto keyComponent = mKeyComponents.at (nextTransposeNote);
            keyComponent->setNoteColor (COLOR_PURPLE);
        }
    }

    if (mControlsState.isTransposeLocked())
    {
        if (nextTransposeNote == -1)
        {
            auto keyComponent = mKeyComponents.at (prevTransposeNote);
            keyComponent->setNoteColor (keyComponent->getDefaultColor (prevTransposeNote));
        }

        if (nextTransposeNote > 0)
        {
            auto keyComponent = mKeyComponents.at (nextTransposeNote);
            keyComponent->setNoteColor (COLOR_PURPLE);

            if (prevTransposeNote > 0)
            {
                auto keyComponent = mKeyComponents.at (prevTransposeNote);
                keyComponent->setNoteColor (keyComponent->getDefaultColor (prevTransposeNote));
            }
        }
    }
}

void InputKeyboardComponent::handleTransposeBaseChanged (const DataMessage* inMessage)
{
    int prevTransposeBase = inMessage->messageVar1;
    int nextTransposeBase = inMessage->messageVar2;

    turnOffTransposeKeys (prevTransposeBase);
    turnOnTransposeKeys (nextTransposeBase);
}

void InputKeyboardComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    int nextTransposeBase = inMessage->messageVar1;
    if (!mControlsState.isTransposeOff()) { turnOnTransposeKeys (nextTransposeBase); }
    if (mControlsState.isTransposeOff()) { turnOffTransposeKeys (nextTransposeBase); }
}

//==============================================================================
void InputKeyboardComponent::turnOnTransposeKeys (const int transposeBase)
{
    for (int index = transposeBase; index < transposeBase + 25; index++)
    {
        auto keyComponent = mKeyComponents.at (index);
        Colour markerColor = index == transposeBase + 12 ? COLOR_RED : COLOR_PURPLE;

        keyComponent->setNoteColor (keyComponent->getDefaultColor (index));
        keyComponent->setMarkerColor (markerColor);
    }
}

void InputKeyboardComponent::turnOffTransposeKeys (const int transposeBase)
{
    juce::Array<int> presetInputNotes = mPresetState.getPresetInputNotes();

    for (int index = transposeBase; index < transposeBase + 25; index++)
    {
        auto keyComponent = mKeyComponents.at (index);
        bool isPresetNote = presetInputNotes.contains (index);
        Colour defaultColor = keyComponent->getDefaultColor (index);

        keyComponent->setNoteColor (defaultColor);
        keyComponent->setMarkerColor (isPresetNote ? COLOR_BLUE : defaultColor);
    }
}
