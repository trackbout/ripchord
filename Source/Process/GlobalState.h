#pragma once

#include "JuceHeader.h"
#include "DataMessage.h"
#include "DataMessageBroadcaster.h"

//==============================================================================
class GlobalState : public DataMessageBroadcaster
{
public:
    //==============================================================================
    GlobalState();
    ~GlobalState();

    //==============================================================================
    enum Mode { Play, Edit };
    enum View { Keyboard, Preset };
    enum Right { RightOff, RightOn };
    enum Menu { Hidden, Visible };

    //==============================================================================
    void toggleMode();
    bool isPlayMode();
    bool isEditMode();

    //==============================================================================
    void toggleView();
    bool isKeyboardView();
    bool isPresetView();

    //==============================================================================
    void toggleRightClick();
    bool isRightClickOff();
    bool isRightClickOn();

    //==============================================================================
    void toggleMenu();
    bool isMenuHidden();
    bool isMenuVisible();

private:
    //==============================================================================
    Mode mMode = Mode::Play;
    View mView = View::Keyboard;
    Right mRight = Right::RightOff;
    Menu mMenu = Menu::Hidden;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalState)
};
