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
}

bool GlobalState::isInPlayMode()
{
    return mMode == Mode::Play;
}

bool GlobalState::isInEditMode()
{
    return mMode == Mode::Edit;
}
