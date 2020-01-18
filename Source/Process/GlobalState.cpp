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
    message->messageCode = MessageCode::kToggleMode;
    sendMessage (message, ListenerType::kSync);
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
    message->messageCode = MessageCode::kToggleView;
    sendMessage (message, ListenerType::kSync);
}

bool GlobalState::isKeyboardView()
{
    return mView == View::Keyboard;
}

bool GlobalState::isPresetView()
{
    return mView == View::Preset;
}

//==============================================================================
void GlobalState::toggleMenu()
{
    mMenu = isMenuHidden() ? Menu::Visible : Menu::Hidden;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleMenu;
    sendMessage (message, ListenerType::kSync);
}

bool GlobalState::isMenuHidden()
{
    return mMenu == Menu::Hidden;
}

bool GlobalState::isMenuVisible()
{
    return mMenu == Menu::Visible;
}
