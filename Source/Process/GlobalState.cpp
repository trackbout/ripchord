#include "GlobalState.h"

//==============================================================================
GlobalState::GlobalState()
{
}

GlobalState::~GlobalState()
{
}

//==============================================================================
void GlobalState::toggleTheme()
{
    mTheme = isDarkTheme() ? Theme::Light : Theme::Dark;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleTheme;
    sendMessage (message, ListenerType::kSync);
}

bool GlobalState::isDarkTheme()
{
    return mTheme == Theme::Dark;
}

bool GlobalState::isLightTheme()
{
    return mTheme == Theme::Light;
}

//==============================================================================
void GlobalState::togglePower()
{
    mPower = isPowerOn() ? Power::Off : Power::On;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kTogglePower;
    sendMessage (message, ListenerType::kSync);
}

bool GlobalState::isPowerOn()
{
    return mPower == Power::On;
}

bool GlobalState::isPowerOff()
{
    return mPower == Power::Off;
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
void GlobalState::toggleRightClick()
{
    mRight = isRightClickOff() ? Right::RightOn : Right::RightOff;

    DataMessage* message = new DataMessage();
    message->messageCode = MessageCode::kToggleRight;
    sendMessage (message, ListenerType::kSync);
}

bool GlobalState::isRightClickOff()
{
    return mRight == Right::RightOff;
}

bool GlobalState::isRightClickOn()
{
    return mRight == Right::RightOn;
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

//==============================================================================
int GlobalState::getMouseDownX()
{
    return mMouseDownX;
}

int GlobalState::getMouseDownY()
{
    return mMouseDownY;
}

int GlobalState::getMouseDownKey()
{
    return mMouseDownKey;
}

//==============================================================================
void GlobalState::setMouseDownX (int inX)
{
    mMouseDownX = inX;
}

void GlobalState::setMouseDownY (int inY)
{
    mMouseDownY = inY;
}

void GlobalState::setMouseDownKey (int inNoteNumber)
{
    mMouseDownKey = inNoteNumber;
}

//==============================================================================
XmlElement* GlobalState::exportGlobalStateXml()
{
    XmlElement* globalStateXml = new XmlElement ("GlobalState");

    globalStateXml->setAttribute ("dark", isDarkTheme());

    return globalStateXml;
}

void GlobalState::importGlobalStateXml (XmlElement* inGlobalStateXml)
{
    mTheme = inGlobalStateXml->getBoolAttribute ("dark") ? Theme::Dark : Theme::Light;
}
