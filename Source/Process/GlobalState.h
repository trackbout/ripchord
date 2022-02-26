#pragma once

#include "JuceHeader.h"
#include "System.h"
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
    void toggleTheme();
    bool isDarkTheme();
    bool isLightTheme();

    //==============================================================================
    void togglePower();
    bool isPowerOn();
    bool isPowerOff();

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

    //==============================================================================
    int getMouseDownX();
    int getMouseDownY();
    int getMouseDownKey();

    //==============================================================================
    void setMouseDownX (int x);
    void setMouseDownY (int y);
    void setMouseDownKey (int noteNumber);

    //==============================================================================
    void readConfigFile();

private:
    //==============================================================================
    enum Theme { Dark, Light };
    enum Power { On, Off };
    enum Mode { Play, Edit };
    enum View { Keyboard, Preset };
    enum Right { RightOff, RightOn };
    enum Menu { Hidden, Visible };

    Theme mTheme = Theme::Light;
    Power mPower = Power::On;
    Mode mMode = Mode::Play;
    View mView = View::Keyboard;
    Right mRight = Right::RightOff;
    Menu mMenu = Menu::Hidden;

    int mMouseDownX;
    int mMouseDownY;
    int mMouseDownKey;

    PropertiesFile mConfigFile { System::createPluginPropertiesOptions ("config") };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalState)
};
