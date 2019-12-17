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

    //==============================================================================
    void toggleMode();
    bool isPlayMode();
    bool isEditMode();

    //==============================================================================
    void toggleView();
    bool isKeyboardView();
    bool isPresetView();

private:
    //==============================================================================
    Mode mMode = Mode::Play;
    View mView = View::Keyboard;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalState)
};
