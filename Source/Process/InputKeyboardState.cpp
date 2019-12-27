#include "InputKeyboardState.h"

//==============================================================================
InputKeyboardState::InputKeyboardState()
{
}

InputKeyboardState::~InputKeyboardState()
{
}

//==============================================================================
int InputKeyboardState::getSelectedEditNote()
{
    return mSelectedEditNote;
}

void InputKeyboardState::setSelectedEditNote (int inNoteNumber)
{
    const int prevSelectedEditNote = mSelectedEditNote;
    const int nextSelectedEditNote = inNoteNumber;
    mSelectedEditNote = nextSelectedEditNote;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kSelectedEditNote;
    message->messageData0 = prevSelectedEditNote;
    message->messageData1 = nextSelectedEditNote;
    sendMessage (message, ListenerType::kSync);
}
