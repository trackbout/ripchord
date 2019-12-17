#include "GlobalState.h"

//==============================================================================
GlobalState::GlobalState()
{
}

GlobalState::~GlobalState()
{
}

//==============================================================================
void GlobalState::toggleMode()
{
    mMode = isPlayMode() ? Mode::Edit : Mode::Play;

    DataMessage* message = new DataMessage();
    message->messageCode = DataMessageCode::kModeUpdated;
    sendMessage (message, kListenerType_Sync);
}

bool GlobalState::isPlayMode()
{
    return mMode == Mode::Play;
}

bool GlobalState::isEditMode()
{
    return mMode == Mode::Edit;
}

//==============================================================================
void GlobalState::toggleView()
{
    mView = isKeyboardView() ? View::Preset : View::Keyboard;

    DataMessage* message = new DataMessage();
    message->messageCode = DataMessageCode::kViewUpdated;
    sendMessage (message, kListenerType_Sync);
}

bool GlobalState::isKeyboardView()
{
    return mView == View::Keyboard;
}

bool GlobalState::isPresetView()
{
    return mView == View::Preset;
}
