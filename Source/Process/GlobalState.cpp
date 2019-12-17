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
    mMode = isInPlayMode() ? Mode::Edit : Mode::Play;

    DataMessage* message = new DataMessage();
    message->messageCode = DataMessageCode::kModeUpdated;
    message->messageData0 = "WOOT";
    sendMessage (message, kListenerType_Sync);
}

bool GlobalState::isInPlayMode()
{
    return mMode == Mode::Play;
}

bool GlobalState::isInEditMode()
{
    return mMode == Mode::Edit;
}
