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
    mSelectedEditNote = inNoteNumber;
}
