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
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kAsync);
    mControlsState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mPresetState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
    mMidiState.DataMessageBroadcaster::addListener (this, ListenerType::kAsync);
    mMidiState.DataMessageBroadcaster::addListener (this, ListenerType::kSync);
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

        keyComponent->onRightClick = [this](const int inInputNote, const MouseEvent& inEvent)
        {
            if (mGlobalState.isPlayMode()) { return; }
            DBG ("onRightClick");
        };
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
        case (MessageCode::kEditModeShiftArrow): { handleEditModeShiftArrow (inMessage); } break;
        case (MessageCode::kActiveTransposeNoteAllowed): { handleActiveTransposeNoteAllowed (inMessage); } break;
        case (MessageCode::kActiveTransposeNote): { handleActiveTransposeNote (inMessage); } break;
        case (MessageCode::kToggleTranspose): { handleToggleTranspose (inMessage); } break;
        case (MessageCode::kTransposeBase): { handleTransposeBase (inMessage); } break;
        case (MessageCode::kInputNoteOff): { handleInputNoteOff (inMessage); } break;
        case (MessageCode::kInputNoteOn): { handleInputNoteOn (inMessage); } break;
        default: { } break;
    };
}

void InputKeyboardComponent::handleToggleMode (const DataMessage* inMessage)
{
    resetKeyColors();
    mPresetState.resetEditModeInputNote();
    juce::Array<int> presetInputNotes = mPresetState.getPresetInputNotes();
    Colour markerColor = mGlobalState.isEditMode() ? COLOR_GREEN : COLOR_BLUE;

    for (int& inputNote : presetInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->setNoteColor (keyComponent->getDefaultColor());
        keyComponent->setMarkerColor (markerColor);
    }

    if (mGlobalState.isPlayMode() && mControlsState.isTransposeOn())
    {
        turnOnTransposeKeys (mControlsState.getTransposeBase());
    }
}

void InputKeyboardComponent::handlePresetFileNew (const DataMessage* inMessage)
{
    resetKeyColors();
    if (mControlsState.isTransposeOn()) { mControlsState.toggleTranspose(); }
}

void InputKeyboardComponent::handlePresetFileLoaded (const DataMessage* inMessage)
{
    resetKeyColors();
    if (mControlsState.isTransposeOn()) { mControlsState.toggleTranspose(); }

    juce::Array<int> presetInputNotes = inMessage->messageArray1;

    for (int& inputNote : presetInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->setMarkerColor (COLOR_BLUE);
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
        auto defaultColor = keyComponent->getDefaultColor();

        if (prevEditModeInputNoteContainsChord) { keyComponent->setNoteColor (defaultColor); }
        else { keyComponent->setNoteAndMarkerColor (defaultColor); }
    }

    if (nextEditModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (nextEditModeInputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
    }
}

void InputKeyboardComponent::handleEditModeShiftArrow (const DataMessage* inMessage)
{
    const int prevEditModeInputNote = inMessage->messageVar1;
    const int nextEditModeInputNote = inMessage->messageVar2;
    juce::Array<int> prevPresetInputNotes = inMessage->messageArray1;
    juce::Array<int> nextPresetInputNotes = inMessage->messageArray2;

    if (prevEditModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (prevEditModeInputNote);
        auto defaultColor = keyComponent->getDefaultColor();
        keyComponent->setNoteAndMarkerColor (defaultColor);
    }

    for (int& inputNote : prevPresetInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        auto defaultColor = keyComponent->getDefaultColor();
        keyComponent->setNoteAndMarkerColor (defaultColor);
    }

    for (int& inputNote : nextPresetInputNotes)
    {
        auto keyComponent = mKeyComponents.at (inputNote);
        keyComponent->setMarkerColor (COLOR_GREEN);
    }

    if (nextEditModeInputNote > 0)
    {
        auto keyComponent = mKeyComponents.at (nextEditModeInputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
    }
}

void InputKeyboardComponent::handleActiveTransposeNoteAllowed (const DataMessage* inMessage)
{
    if (mMidiState.getCurrentlyOnInputNotes().size() > 0) { return; }
    mControlsState.setActiveTransposeNote (inMessage->messageVar1);
}

void InputKeyboardComponent::handleActiveTransposeNote (const DataMessage* inMessage)
{
    const int prevActiveTransposeNote = inMessage->messageVar1;
    const int nextActiveTransposeNote = inMessage->messageVar2;

    if (nextActiveTransposeNote == -1)
    {
        auto keyComponent = mKeyComponents.at (prevActiveTransposeNote);
        keyComponent->setNoteColor (keyComponent->getDefaultColor());
    }

    if (nextActiveTransposeNote > 0)
    {
        auto keyComponent = mKeyComponents.at (nextActiveTransposeNote);
        keyComponent->setNoteColor (COLOR_PURPLE);

        if (prevActiveTransposeNote > 0)
        {
            auto keyComponent = mKeyComponents.at (prevActiveTransposeNote);
            keyComponent->setNoteColor (keyComponent->getDefaultColor());
        }
    }
}

void InputKeyboardComponent::handleToggleTranspose (const DataMessage* inMessage)
{
    int nextTransposeBase = inMessage->messageVar1;
    if (mControlsState.isTransposeOn()) { turnOnTransposeKeys (nextTransposeBase); }
    if (mControlsState.isTransposeOff()) { turnOffTransposeKeys (nextTransposeBase); }
}

void InputKeyboardComponent::handleTransposeBase (const DataMessage* inMessage)
{
    int prevTransposeBase = inMessage->messageVar1;
    int nextTransposeBase = inMessage->messageVar2;

    turnOffTransposeKeys (prevTransposeBase);
    turnOnTransposeKeys (nextTransposeBase);
}

void InputKeyboardComponent::handleInputNoteOff (const DataMessage* inMessage)
{
    int inputNote = inMessage->messageVar1;
    int editModeInputNote = mPresetState.getEditModeInputNote();

    auto keyComponent = mKeyComponents.at (inputNote);
    bool containsChord = mPresetState.getPresetInputNotes().contains (inputNote);
    Colour markerColor = mGlobalState.isEditMode() ? COLOR_GREEN : COLOR_BLUE;
    Colour defaultColor = keyComponent->getDefaultColor();
    keyComponent->setMarkerColor (containsChord ? markerColor : defaultColor);
    keyComponent->setNoteColor (defaultColor);

    if (editModeInputNote > 0 && inputNote == editModeInputNote)
    {
        auto keyComponent = mKeyComponents.at (editModeInputNote);
        keyComponent->setNoteAndMarkerColor (COLOR_GREEN);
    }
}

void InputKeyboardComponent::handleInputNoteOn (const DataMessage* inMessage)
{
    int inputNote = inMessage->messageVar1;

    auto keyComponent = mKeyComponents.at (inputNote);
    keyComponent->setNoteAndMarkerColor (COLOR_BLUE);
}

//==============================================================================
void InputKeyboardComponent::turnOnTransposeKeys (const int transposeBase)
{
    for (int index = transposeBase; index < transposeBase + 25; index++)
    {
        auto keyComponent = mKeyComponents.at (index);
        Colour markerColor = index == transposeBase + 12 ? COLOR_RED : COLOR_PURPLE;

        keyComponent->setNoteColor (keyComponent->getDefaultColor());
        keyComponent->setMarkerColor (markerColor);
    }

    if (mControlsState.getActiveTransposeNote() > 0)
    {
        auto keyComponent = mKeyComponents.at (mControlsState.getActiveTransposeNote());
        keyComponent->setNoteColor (COLOR_PURPLE);
    }
}

void InputKeyboardComponent::turnOffTransposeKeys (const int transposeBase)
{
    juce::Array<int> presetInputNotes = mPresetState.getPresetInputNotes();

    for (int index = transposeBase; index < transposeBase + 25; index++)
    {
        auto keyComponent = mKeyComponents.at (index);
        bool isPresetNote = presetInputNotes.contains (index);
        Colour defaultColor = keyComponent->getDefaultColor();

        keyComponent->setNoteColor (defaultColor);
        keyComponent->setMarkerColor (isPresetNote ? COLOR_BLUE : defaultColor);
    }
}
